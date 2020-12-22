#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_stateIdle = new PlayerStateIdle(this);
	m_stateMove = new PlayerStateMove(this);
	//待機ステートに切り替える
	ChangeState(m_stateIdle);
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

	m_animClip[0].Load("Assets/animData/Rifle_Idle.tka");
	m_animClip[0].SetLoopFlag(true);
	m_animClip[1].Load("Assets/animData/Rifle_Walk.tka");
	m_animClip[1].SetLoopFlag(true);
	m_animClip[2].Load("Assets/animData/Rifle_Run_60.tka");
	m_animClip[2].SetLoopFlag(true);
	m_animClip[3].Load("Assets/animData/Rifle_Sprint.tka");
	m_animClip[3].SetLoopFlag(true);

	m_playerModel = NewGO<prefab::ModelRender>(1, nullptr);
	m_playerModel->SetTkmFilePath("Assets/modelData/soldier_bs01.tkm");
	m_playerModel->SetVSEntryPoint("VSMainSkin");
	m_playerModel->SetSkeleton(m_skeleton);
	m_scale *= 0.8f;
	m_playerModel->SetScale(m_scale);
	m_playerModel->SetShadowRecieverFlag(true);

	//スケルトンとアニメーションの初期化
	m_skeleton.Init("Assets/modelData/soldier_bs01.tks");
	m_skeleton.Update(Matrix::Identity);
	m_animation.Init(m_skeleton, m_animClip, 4);
	m_animation.Play(0);
	return true;
}

void Player::Update()
{
	//待機ステートに切り替える
	ChangeState(m_stateIdle);

	float DeltaTime = g_gameTime.GetFrameDeltaTime();
	Vector3 footStepValue = Vector3::Zero;
	//アニメーションからfootstepの移動量を持ってくる
	footStepValue = m_animation.Update(DeltaTime);
	//Maxとは軸が違うので軸を合わせる
	float value = footStepValue.y;
	footStepValue.y = footStepValue.z;
	footStepValue.z = -value;
	footStepValue *= 24 * DeltaTime;

	if (g_pad[0]->GetLStickXF() != 0.0f || g_pad[0]->GetLStickYF() != 0.0f)
	{
		ChangeState(m_stateMove);
	}

	currentState->Update();

	m_rot.Apply(footStepValue);
	m_pos += footStepValue;

	m_camera->SetTarget(m_pos);

	m_playerModel->SetPosition(m_pos);
	m_playerModel->SetRotation(m_rot);
}