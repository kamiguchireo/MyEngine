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
	if (m_camera != nullptr)
	{
		DeleteGO(m_camera);
		m_camera = nullptr;
	}
	if (m_stateIdle != nullptr)
	{
		delete m_stateIdle;
		m_stateIdle = nullptr;
	}
	if (m_stateMove != nullptr)
	{
		delete m_stateMove;
		m_stateMove = nullptr;
	}
	if (m_stateAim != nullptr)
	{
		delete m_stateAim;
		m_stateAim = nullptr;
	}
	if (m_PlayerWeapon != nullptr)
	{
		DeleteGO(m_PlayerWeapon);
		m_PlayerWeapon = nullptr;
	}
}

void Player::ChangeState(IPlayer* state)
{
	currentState = state;
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
	//�A�j���[�V������������
	m_animation.Init(m_skeleton, m_animClip, 6);
	m_animation.Play(0);

	//�����New
	m_PlayerWeapon = NewGO <Weapon>(2);
	//�����������
	m_PlayerWeapon->Init(&m_skeleton,true);

	return true;
}

void Player::Update()
{
	//�ҋ@�X�e�[�g�ɐ؂�ւ���
	ChangeState(m_stateIdle);
	
	float DeltaTime = g_gameTime.GetFrameDeltaTime();
	Vector3 footStepValue = Vector3::Zero;
	//�A�j���[�V��������footstep�̈ړ��ʂ������Ă���
	footStepValue = m_animation.Update(DeltaTime);
	//Max�Ƃ͎����Ⴄ�̂Ŏ������킹��
	float value = footStepValue.y;
	footStepValue.y = footStepValue.z;
	footStepValue.z = -value;
	//�t�b�g�X�e�b�v�𒲐�
	footStepValue *= footStepAdjustValue;
	//�d�͂����Z
	footStepValue += gravity;

	//���X�e�B�b�N�����͂���Ă���Ƃ�
	if (g_pad[0]->GetLStickXF() != 0.0f || g_pad[0]->GetLStickYF() != 0.0f)
	{
		//�X�e�[�g��m_stateMove�ɕύX
		ChangeState(m_stateMove);
	}

	//�E�N���b�N���ꂽ�Ƃ�
	if (GetKeyState(VK_RBUTTON))
	{
		//�G�C���J�����ɐ؂�ւ�
		m_camera->SetCameraState(CameraState::AIM);
		ChangeState(m_stateAim);
		Vector3 aimForward = g_camera3D->GetForward();
		aimForward.y = 0.0f;
		//�v���C���[�����_�����ɉ�]
		m_rot.SetRotation(m_forward, aimForward);
	}
	else
	{
		//TPS�J�����ɐ؂�ւ�
		m_camera->SetCameraState(CameraState::TPS);
		Vector3 aimForward = g_camera3D->GetForward();
		aimForward.y = 0.0f;
	}
	currentState->Update();
	//footStepValue�ɉ�]��K�p
	m_rot.Apply(footStepValue);
	//�L�����R���̌v�Z
	Vector3 returnPos = characon.Execute(footStepValue, DeltaTime);

	m_pos = returnPos;

	//�J�����̃^�[�Q�b�g���Z�b�g
	m_camera->SetTarget(m_pos);

	//�|�W�V�������Z�b�g
	m_playerModel->SetPosition(m_pos);
	//��]���Z�b�g
	m_playerModel->SetRotation(m_rot);

	//������A�b�v�f�[�g
	m_PlayerWeapon->Update();
}