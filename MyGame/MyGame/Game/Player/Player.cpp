#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//待機ステートに切り替える
	ChangeState(&m_stateIdle);
}

Player::~Player()
{
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
}

void Player::ChangeState(IPlayer* state)
{
	currentState = state;
}

bool Player::Start()
{
	m_camera = NewGO<GameCamera>(0, nullptr);

	m_animClip[0].Load("Assets/animData/Idle.tka");
	m_animClip[0].SetLoopFlag(true);
	//m_animClip[1].Load("Assets/animData/run.tka");
	//m_animClip[1].SetLoopFlag(true);

	m_playerModel = NewGO<prefab::ModelRender>(1, nullptr);
	m_playerModel->SetTkmFilePath("Assets/modelData/unityChan.tkm");
	m_playerModel->SetVSEntryPoint("VSMainSkin");
	m_playerModel->SetSkeleton(m_skeleton);
	m_rot.SetRotationDeg(Vector3::AxisX, 90.0f);
	//m_playerModel->SetScale(/*m_scale*/{0.8f, 0.8f, 0.8f});
	m_playerModel->SetShadowRecieverFlag(true);

	//スケルトンとアニメーションの初期化
	m_skeleton.Init("Assets/modelData/unityChan.tks");
	m_skeleton.Update(Matrix::Identity);
	m_animation.Init(m_skeleton, m_animClip, 1);
	m_animation.Play(1);
	return true;
}

void Player::Update()
{
	m_animation.Update(g_gameTime.GetFrameDeltaTime()*2);
	if (g_pad[0]->GetLStickXF() != 0.0f||g_pad[0]->GetLStickYF() != 0.0f)
	{
		ChangeState(&m_stateMove);
	}

	currentState->Update(m_pos,m_rot);
	
	m_camera->SetTarget(m_pos);

	m_playerModel->SetPosition(m_pos);
	m_playerModel->SetRotation(m_rot);
	
}