#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//�X�e�[�g��new
	m_stateIdle = new PlayerStateIdle(this);
	m_stateMove = new PlayerStateMove(this);
	m_stateAim = new PlayerStateAim(this);
	//�ҋ@�X�e�[�g�ɐ؂�ւ���
	ChangeState(m_stateIdle);
}

Player::~Player()
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
	//�q�b�g�{�b�N�X
	if (m_HitBox != nullptr)
	{
		DeleteGO(m_HitBox);
		m_HitBox = nullptr;
	}
}

bool Player::Start()
{
	m_camera = NewGO<GameCamera>(0, nullptr);

	characon.Init(15.0f,115.0f, m_pos);
	//�ҋ@��Ԃ̃A�j���[�V����
	m_animClip[enPlayerAnimation_Rifle_Idle].Load("Assets/animData/Rifle_Idle.tka");
	m_animClip[enPlayerAnimation_Rifle_Idle].SetLoopFlag(true);
	//������Ԃ̃A�j���[�V����
	m_animClip[enPlayerAnimation_Rifle_Walk].Load("Assets/animData/Rifle_Walk.tka");
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
	m_animation.Init(m_skeleton, m_animClip, 6);
	m_animation.Play(0);

	//�����New
	m_PlayerWeapon = NewGO <Weapon>(2);
	//�����������
	m_PlayerWeapon->Init(&m_skeleton,true);

	//�X�v���C�g��New
	m_AimFramesprite = NewGO<prefab::SpriteRender>(3, nullptr);
	//������
	m_AimFramesprite->Init("Assets/Image/AimFrame.dds", 100, 100);

	m_HitBox = NewGO<PlayerHitBox>(4, nullptr);
	m_HitBox->Init(&m_skeleton, this);

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
	//�E�N���b�N���ꂽ�Ƃ�
	if (GetKeyState(VK_RBUTTON))
	{
		//�Ə��̃���1�ɂ���
		m_AimFramesprite->SetAlpha(1.0f);
		//�G�C���J�����ɐ؂�ւ�
		m_camera->SetCameraState(CameraState::AIM);
		ChangeState(m_stateAim);
	}
	else
	{
		//�Ə��̃���0�ɂ���
		m_AimFramesprite->SetAlpha(0.0f);
		//TPS�J�����ɐ؂�ւ�
		m_camera->SetCameraState(CameraState::TPS);
	}
}

void Player::Update()
{
	//�ҋ@�X�e�[�g�ɐ؂�ւ���
	ChangeState(m_stateIdle);
	
	//1�t���[���ɂ����������Ԃ��擾
	float DeltaTime = g_gameTime.GetFrameDeltaTime();
	//�A�j���[�V��������footstep�̈ړ��ʂ������Ă���
	footStepValue = m_animation.Update(DeltaTime);
	
	AxisTrans();
	
	//�t�b�g�X�e�b�v�𒲐�
	footStepValue *= footStepAdjustValue;

	//�d�͂����Z
	if (characon.IsOnGround())
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

	//�ړ��̏���
	Move();

	//�\���鏈��
	Hold();

	//���݂̃X�e�[�g�̍X�V
	currentState->Update();
	//footStepValue�ɉ�]��K�p
	m_rot.Apply(footStepValue);
	//�L�����R���̌v�Z
	Vector3 returnPos = characon.Execute(footStepValue, DeltaTime);
	//�|�W�V�����Ɍv�Z�ŋA���Ă����l����
	m_pos = returnPos;

	//�J�����̃^�[�Q�b�g���Z�b�g
	m_camera->SetPivotPos(m_pos);
	m_camera->SetHeadPos(m_skeleton.GetBone(m_HeadBoneNum)->GetPosition());
	//�|�W�V�������Z�b�g
	m_playerModel->SetPosition(m_pos);
	//��]���Z�b�g
	m_playerModel->SetRotation(m_rot);

}