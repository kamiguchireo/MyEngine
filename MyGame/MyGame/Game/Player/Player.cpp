#include "stdafx.h"
#include "Player.h"
#include "Game/Camera/GameCamera.h"
#include "IPlayer.h"
#include "PlayerStateIdle.h"
#include "PlayerStateMove.h"
#include "PlayerStateAim.h"
#include "PlayerHitBox.h"
#include "Game/Game.h"

Player* Player::m_Instance = nullptr;
Player::Player()
{
	m_Instance = this;
}

Player::~Player()
{

}

void Player::OnDestroy()
{
	//�������
	if (m_playerModel != nullptr)
	{
		DeleteGO(m_playerModel);
		m_playerModel = nullptr;
	}
	//�J����
	if (m_camera != nullptr)
	{
		DeleteGO(m_camera);
		m_camera = nullptr;
	}
	//�ҋ@�X�e�[�g
	if (m_stateIdle != nullptr)
	{
		delete m_stateIdle;
		m_stateIdle = nullptr;
	}
	//�ړ��X�e�[�g
	if (m_stateMove != nullptr)
	{
		delete m_stateMove;
		m_stateMove = nullptr;
	}
	//�G�C���X�e�[�g
	if (m_stateAim != nullptr)
	{
		delete m_stateAim;
		m_stateAim = nullptr;
	}
	//����
	if (m_PlayerWeapon != nullptr)
	{
		DeleteGO(m_PlayerWeapon);
		m_PlayerWeapon = nullptr;
	}
	//�X�v���C�g
	if (m_AimFramesprite != nullptr)
	{
		DeleteGO(m_AimFramesprite);
		m_AimFramesprite = nullptr;
	}
	if (m_DiedSprite != nullptr)
	{
		DeleteGO(m_DiedSprite);
		m_DiedSprite = nullptr;
	}
	//�q�b�g�{�b�N�X
	if (m_HitBox != nullptr)
	{
		DeleteGO(m_HitBox);
		m_HitBox = nullptr;
	}
	if (characon != nullptr)
	{
		delete characon;
		characon = nullptr;
	}
	if (m_HoldRifleSound != nullptr)
	{
		m_HoldRifleSound->Stop();
		DeleteGO(m_HoldRifleSound);
		m_HoldRifleSound = nullptr;
	}
}

bool Player::Start()
{
	//�v���C���[�̃X�e�[�^�X
	m_Status = std::make_unique<PlayerStatus>(this);

	//�X�e�[�g��new
	m_stateIdle = new PlayerStateIdle(this);
	m_stateMove = new PlayerStateMove(this);
	m_stateAim = new PlayerStateAim(this);
	characon = new CharacterController();
	//�ҋ@�X�e�[�g�ɐ؂�ւ���
	ChangeState(m_stateIdle);

	m_camera = NewGO<GameCamera>(0, nullptr);

	characon->Init(15.0f,115.0f, m_pos);

	characon->GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Player);

	//�ҋ@��Ԃ̃A�j���[�V����
	m_animClip[enPlayerAnimation_Rifle_Idle].Load("Assets/animData/Rifle_Idle.tka");
	m_animClip[enPlayerAnimation_Rifle_Idle].SetLoopFlag(true);
	//������Ԃ̃A�j���[�V����
	m_animClip[enPlayerAnimation_Rifle_Walk].Load("Assets/animData/Rifle_Walk_Forward.tka");
	m_animClip[enPlayerAnimation_Rifle_Walk].SetLoopFlag(true);
	//�����Ԃ̃A�j���[�V����
	m_animClip[enPlayerAnimation_Rifle_Run].Load("Assets/animData/Rifle_Run.tka");
	m_animClip[enPlayerAnimation_Rifle_Run].SetLoopFlag(true);
	//�X�v�����g��Ԃ̃A�j���[�V����
	m_animClip[enPlayerAnimation_Rifle_Sprint].Load("Assets/animData/Rifle_Sprint.tka");
	m_animClip[enPlayerAnimation_Rifle_Sprint].SetLoopFlag(true);
	//�G�C����Ԃ̃A�j���[�V����
	m_animClip[enPlayerAnimation_Rifle_Down_To_Aim].Load("Assets/animData/Rifle_Down_To_Aim.tka");
	m_animClip[enPlayerAnimation_Rifle_Down_To_Aim].SetLoopFlag(false);
	//���C��Ԃ̃A�j���[�V����
	m_animClip[enPlayerAnimation_Rifle_fire].Load("Assets/animData/Rifle_fire.tka");
	m_animClip[enPlayerAnimation_Rifle_fire].SetLoopFlag(true);
	m_animClip[enPlayerAnimation_Firing_Rifle].Load("Assets/animData/Firing_Rifle.tka");
	m_animClip[enPlayerAnimation_Firing_Rifle].SetLoopFlag(true);
	//���S�A�j���[�V����
	m_animClip[enPlayerAnimation_Death_From_Front].Load("Assets/animData/Death_From_Front.tka");
	m_animClip[enPlayerAnimation_Death_From_Front].SetLoopFlag(false);

	//���f����New
	m_playerModel = NewGO<prefab::ModelRender>(1, nullptr);
	//�t�@�C���p�X
	m_playerModel->SetTkmFilePath("Assets/modelData/soldier_bs01.tkm");
	//���_�V�F�[�_�[�̃G���g���[�|�C���g
	m_playerModel->SetVSEntryPoint("VSMainSkin");
	//�X�P���g�����Z�b�g
	m_playerModel->SetSkeleton(m_skeleton);
	//�X�P�[�����Z�b�g
	m_playerModel->SetScale(m_scale);
	//�V���h�E���V�[�o�[�ɂ���
	m_playerModel->SetShadowRecieverFlag(true);
	//�f�B�U�����O��K������
	m_playerModel->SetDitherFlag(true);

	//�X�P���g���ƃA�j���[�V�����̏�����
	m_skeleton.Init("Assets/modelData/soldier_bs01.tks");

	//�X�P���g���̃A�b�v�f�[�g
	m_skeleton.Update(Matrix::Identity);

	//���̃{�[���ԍ����擾
	m_HeadBoneNum = m_skeleton.FindBoneID(L"mixamorig:Head");
	//�A�j���[�V������������
	m_animation.Init(m_skeleton, m_animClip, enPlayerAnimation_Num);
	m_animation.Play(enPlayerAnimation_Rifle_Idle);

	//�����New
	m_PlayerWeapon = NewGO <Weapon>(2);
	//�����������
	m_PlayerWeapon->Init(&m_skeleton,true);
	m_PlayerWeapon->SetCharacter(enCollisionAttr_Player);

	//�X�v���C�g��New
	m_AimFramesprite = NewGO<prefab::SpriteRender>(3, nullptr);
	m_DiedSprite = NewGO<prefab::SpriteRender>(4, nullptr);
	//������
	m_AimFramesprite->Init("Assets/Image/AimFrame.dds", 100, 100);
	m_DiedSprite->Init("Assets/Image/Died.dds", 600, 1500);
	m_DiedSprite->SetAlpha(m_DeadSpriteAlpha);

	m_HitBox = NewGO<PlayerHitBox>(4, nullptr);
	m_HitBox->Init(&m_skeleton, this);

	m_HoldRifleSound = NewGO<SoundSource>(5);
	m_HoldRifleSound->Init(L"Assets/sound/Hold_the_rifle.wav");
	m_HoldRifleSound->SetVolume(1.0f);
	//�G�C���X�e�[�g�̏�����
	m_stateAim->Init();

	return true;
}

void Player::Move()
{
	//���X�e�B�b�N�����͂���Ă���Ƃ�
	if (g_pad[0]->GetLStickXF() != 0.0f || g_pad[0]->GetLStickYF() != 0.0f)
	{
		//�X�e�[�g��m_stateMove�ɕύX
		ChangeState(m_stateMove);
	}
}

void Player::AxisTrans()
{
	//Max�Ƃ͎����Ⴄ�̂Ŏ������킹��
	float value = footStepValue.y;
	footStepValue.y = footStepValue.z;
	footStepValue.z = -value;
}

void Player::Hold()
{
	if (IsRightClick)
	{
		if (!GetAsyncKeyState(VK_RBUTTON))
		{
			IsRightClick = false;
			if (IsAim == false)
			{
				//���C�t�����\���鉹���o��
				m_HoldRifleSound->Play(false,false);
				IsAim = true;
			}
			else
			{
				IsAim = false;
			}
		}
	}
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		IsRightClick = true;
	}
	if (IsAim == true)
	{
		//�Ə��̃���1�ɂ���
		m_AimFramesprite->SetAlpha(1.0f);
		//�G�C���J�����ɐ؂�ւ�
		m_camera->SetCameraState(CameraState::AIM);
		ChangeState(m_stateAim);
	}
	else
	{
		m_HoldRifleSound->Stop();
		//�Ə��̃���0�ɂ���
		m_AimFramesprite->SetAlpha(0.0f);
		//TPS�J�����ɐ؂�ւ�
		m_camera->SetCameraState(CameraState::TPS);
	}
}

void Player::DeadProcess()
{
	auto deltaTime = g_gameTime.GetFrameDeltaTime();
	//�Ə��̃���0�ɂ���
	m_AimFramesprite->SetAlpha(0.0f);
	
	m_DeadSpriteAlpha += m_DeadAlphaFadeSpeed * deltaTime;
	m_DiedSprite->SetAlpha(m_DeadSpriteAlpha);

	//TPS�J�����ɐ؂�ւ�
	if (m_camera != nullptr)
	{
		m_camera->SetCameraState(CameraState::TPS);
	}
	//���Ɏ���ł���ꍇ
	if (m_animation.IsPlaying())
	{
		//�A�j���[�V�������I����Ă��Ȃ��ꍇ
		//���S���̃A�j���[�V�����𗬂�
		m_animation.Play(enPlayerAnimation_Death_From_Front);
		m_animation.Update(deltaTime);
		//�q�b�g�{�b�N�X���c���Ă���Ƃ��폜
		if (m_HitBox != nullptr)
		{
			DeleteGO(m_HitBox);
			m_HitBox = nullptr;
		}
		//�L�����R�����c���Ă���Ƃ��폜
		if (characon != nullptr)
		{
			delete characon;
			characon = nullptr;
		}
		if (m_camera != nullptr)
		{
			DeleteGO(m_camera);
			m_camera = nullptr;
		}
	}
	else
	{
		DeadCameraMove();
		//auto g_game = Game::GetInstance();
		//������x�X�e�[�W01�𐶐����Ȃ���
		//g_game->SceneTrans(SceneNum::enScene_Stage01);
	}
}

void Player::DeadCameraMove()
{
	auto deltaTime = g_gameTime.GetFrameDeltaTime();
	m_DeadLeapTime += deltaTime * m_DeadAfterLeapSpeed;
	m_DeadLeapTime = min(1.0f, m_DeadLeapTime);
	//�ŏI�I�ȃJ�����̈ʒu�ɑ����x�N�g��
	Vector3 CameraAddPos = Vector3::Zero;
	//�O���������Z
	CameraAddPos = m_forward * 100.0f;
	//�J�����̃^�[�Q�b�g��O�����ɉ��Z
	m_DeadAfterCameraTarget = m_pos + CameraAddPos;
	//���������Z
	CameraAddPos.y = 500.0f;
	//�������ɂ���
	CameraAddPos -= m_forward;
	//�ŏI�I�ȃJ�����̈ʒu
	m_DeadAfterCameraPos = m_pos + CameraAddPos;
	//�v���C���[�̌������ɕ⊮�O�̃J����������
	m_LerpForwardCameraPos = m_pos + (m_forward * m_DeadCameraDist * -1.0f);
	m_LerpForwardCameraPos.Lerp(m_DeadLeapTime, m_LerpForwardCameraPos, m_DeadAfterCameraPos);
	//������̌v�Z
	Vector3 cameradir = m_DeadAfterCameraTarget - m_LerpForwardCameraPos;
	if (cameradir.Length() != 0.0f)
	{
		cameradir.Normalize();
	}
	Vector3 right = Cross(Vector3::Up, cameradir);
	if (right.Length() != 0.0f)
	{
		right.Normalize();
	}
	Vector3 m_up = Cross(cameradir, right);
	//�J�����̊e�ݒ���Z�b�g
	g_camera3D->SetPosition(m_LerpForwardCameraPos);
	g_camera3D->SetTarget(m_DeadAfterCameraTarget);
	g_camera3D->SetUp(m_up);
}

void Player::Update()
{
	if (IsDead)
	{
		//�v���C���[�����S������
		DeadProcess();
		return;
	}
	//�ҋ@�X�e�[�g�ɐ؂�ւ���
	ChangeState(m_stateIdle);
	
	//1�t���[���ɂ����������Ԃ��擾
	float DeltaTime = g_gameTime.GetFrameDeltaTime();

	//�ړ��̏���
	Move();

	//�\���鏈��
	Hold();

	//���݂̃X�e�[�g�̍X�V
	currentState->Update();

	//�A�j���[�V��������footstep�̈ړ��ʂ������Ă���
	footStepValue = m_animation.Update(DeltaTime);

	AxisTrans();

	//�t�b�g�X�e�b�v�𒲐�
	//�X�P�[���̒l���Ƃ�
	footStepValue *= m_scale.x;

	//�d�͂����Z
	if (characon->IsOnGround())
	{
		//�n�ʏ�ɂ���Ƃ��͏d�͂����Z�b�g
		m_gravity *= 0.0f;
	}
	else
	{
		//�󒆂ɂ���Ƃ��͏d�͂����Z��������
		m_gravity += gravity;
	}

	//�ړ��ɏd�͂����Z
	footStepValue += m_gravity;

	//footStepValue�ɉ�]��K�p
	m_rot.Apply(footStepValue);

	//�L�����R���̌v�Z
	Vector3 returnPos = characon->Execute(footStepValue);
	//�|�W�V�����Ɍv�Z�ŋA���Ă����l����
	m_pos = returnPos;

	//�J�����̃^�[�Q�b�g���Z�b�g
	m_camera->SetPivotPos(m_pos);
	m_camera->SetHeadPos(m_skeleton.GetBone(m_HeadBoneNum)->GetPosition());
	//�|�W�V�������Z�b�g
	m_playerModel->SetPosition(m_pos);
	//��]���Z�b�g
	m_rot.SetRotation(Vector3::Front, m_forward);
	m_playerModel->SetRotation(m_rot);
	//�T�E���h���X�i�[�̈ʒu���Z�b�g
	g_engine->GetSoundEngine().SetListenerPosition(m_pos);
	//�T�E���h���X�i�[�̑O�������Z�b�g
	g_engine->GetSoundEngine().SetListenerFront((g_camera3D->GetForward()));
	//if (GetAsyncKeyState(VK_LBUTTON))
	//{
	//	m_animation.Play(enPlayerAnimation_Firing_Rifle, 0.3f);
	//	Shooting();
	//}
}