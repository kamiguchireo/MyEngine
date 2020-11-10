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

}

void Player::ChangeState(IPlayer* state)
{
	currentState = state;
}

bool Player::Start()
{
	m_animClip[0].Load("Assets/animData/idle.tka");
	m_animClip[0].SetLoopFlag(true);

	m_playerModel = NewGO<prefab::ModelRender>(0, nullptr);
	m_playerModel->SetTkmFilePath("Assets/modelData/unityChan.tkm");
	m_playerModel->SetVSEntryPoint("VSMainSkin");
	m_playerModel->SetSkeleton(m_skeleton);
	m_rot.SetRotationDeg(Vector3::AxisX, 90.0f);
	m_playerModel->SetScale(m_scale);

	//スケルトンとアニメーションの初期化
	m_skeleton.Init("Assets/modelData/unityChan.tks");
	m_skeleton.Update(Matrix::Identity);
	m_animation.Init(m_skeleton, m_animClip, 1);
	m_animation.Play(0);

	return true;
}

void Player::Update()
{
	m_animation.Update(1.0f / 60.0f);
	if (GetAsyncKeyState(VK_RIGHT))
	{
		ChangeState(&m_stateMove);
	}
	currentState->Update(m_pos,m_rot);

	m_playerModel->SetPosition(m_pos);
	m_playerModel->SetRotation(m_rot);
}