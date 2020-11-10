#include "stdafx.h"
#include "Player.h"
#include "PlayerStateIdle.h"
Player* Player::m_instance = nullptr;
Player::Player()
{
	if (m_instance != nullptr)
	{
		std::abort();
	}
	m_instance = this;
	//待機ステートに切り替える
	ChangeState<PlayerStateIdle>();

}

Player::~Player()
{
	if (currentState != nullptr)
	{
		delete currentState;
		currentState = nullptr;
	}
	if (m_playerModel != nullptr)
	{
		DeleteGO(m_playerModel);
		m_playerModel = nullptr;
	}
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

template<class T>void Player::ChangeState()
{
	if (currentState != nullptr)
	{
		delete currentState;
	}
	//次の状態のインスタンスを作成する
	currentState = new T;
}

bool Player::Start()
{
	m_animClip[0].Load("Assets/animData/idle.tka");
	m_animClip[0].SetLoopFlag(true);

	m_playerModel = NewGO<prefab::ModelRender>(0, nullptr);
	m_playerModel->SetTkmFilePath("Assets / modelData / unityChan.tkm");
	m_playerModel->SetVSEntryPoint("VSMainSkin");
	m_playerModel->SetSkeleton(m_skeleton);
	m_rot.SetRotationDeg(Vector3::AxisX, 90.0f);
	m_playerModel->SetRotation(m_rot);

	//スケルトンとアニメーションの初期化
	m_skeleton.Init("Assets/modelData/unityChan.tks");
	m_skeleton.Update(Matrix::Identity);
	m_animation.Init(m_skeleton, m_animClip, 1);
	m_animation.Play(0);

	return true;
}

void Player::Update()
{
	//m_animation.Update(1.0f / 60.0f);

	currentState->Update();
}

void Player::Draw()
{

}