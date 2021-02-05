#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_stateIdle = new PlayerStateIdle(this);
	m_stateMove = new PlayerStateMove(this);
	m_stateAim = new PlayerStateAim(this);
	m_PlayerWeapon = new PlayerWeapon(this);
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
}

void Player::ChangeState(IPlayer* state)
{
	currentState = state;
}

bool Player::Start()
{
	m_camera = NewGO<GameCamera>(0, nullptr);
	//characon.Init(10.0f, 50.0f, m_pos);
	//�ҋ@��Ԃ̃A�j���[�V����
	m_animClip[0].Load("Assets/animData/Rifle_Idle.tka");
	m_animClip[0].SetLoopFlag(true);
	//������Ԃ̃A�j���[�V����
	m_animClip[1].Load("Assets/animData/Rifle_Walk.tka");
	m_animClip[1].SetLoopFlag(true);
	//�����Ԃ̃A�j���[�V����
	m_animClip[2].Load("Assets/animData/Rifle_Run.tka");
	m_animClip[2].SetLoopFlag(true);
	//�X�v�����g��Ԃ̃A�j���[�V����
	m_animClip[3].Load("Assets/animData/Rifle_Sprint.tka");
	m_animClip[3].SetLoopFlag(true);
	//�G�C����Ԃ̃A�j���[�V����
	m_animClip[4].Load("Assets/animData/Rifle_Down_To_Aim.tka");
	m_animClip[4].SetLoopFlag(false);

	m_playerModel = NewGO<prefab::ModelRender>(1, nullptr);
	m_playerModel->SetTkmFilePath("Assets/modelData/soldier_bs01.tkm");
	m_playerModel->SetVSEntryPoint("VSMainSkin");
	m_playerModel->SetSkeleton(m_skeleton);
	m_scale *= 0.8f;
	m_playerModel->SetScale(m_scale);
	m_playerModel->SetShadowRecieverFlag(true);

	//�X�P���g���ƃA�j���[�V�����̏�����
	m_skeleton.Init("Assets/modelData/soldier_bs01.tks");
	m_skeleton.Update(Matrix::Identity);
	m_animation.Init(m_skeleton, m_animClip, 5);
	m_animation.Play(0);

	m_PlayerWeapon->Start();

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
	footStepValue *= 24 * DeltaTime;

	if (g_pad[0]->GetLStickXF() != 0.0f || g_pad[0]->GetLStickYF() != 0.0f)
	{
		ChangeState(m_stateMove);
	}

	if (GetKeyState(VK_RBUTTON) & 0x80) {
		//�}�E�X�̉E�{�^���������ꂽ"
		ChangeState(m_stateAim);
	}
	currentState->Update();

	m_rot.Apply(footStepValue);
	m_pos += footStepValue;

	m_camera->SetTarget(m_pos);

	m_playerModel->SetPosition(m_pos);
	//characon.Execute(m_pos);
	m_playerModel->SetRotation(m_rot);
	m_PlayerWeapon->Update();
}