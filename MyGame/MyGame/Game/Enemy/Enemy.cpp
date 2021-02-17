#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	if (m_enemyModel != nullptr)
	{
		DeleteGO(m_enemyModel);
		m_enemyModel = nullptr;
	}
}

bool Enemy::Start()
{
	characon.Init(10.0f, 50.0f, m_pos);

	//待機状態のアニメーション
	m_animClip[0].Load("Assets/animData/Rifle_Idle.tka");
	m_animClip[0].SetLoopFlag(true);
	//歩き状態のアニメーション
	m_animClip[1].Load("Assets/animData/Rifle_Walk.tka");
	m_animClip[1].SetLoopFlag(true);
	//走り状態のアニメーション
	m_animClip[2].Load("Assets/animData/Rifle_Run.tka");
	m_animClip[2].SetLoopFlag(true);
	//スプリント状態のアニメーション
	m_animClip[3].Load("Assets/animData/Rifle_Sprint.tka");
	m_animClip[3].SetLoopFlag(true);
	//エイム状態のアニメーション
	m_animClip[4].Load("Assets/animData/Rifle_Down_To_Aim.tka");
	m_animClip[4].SetLoopFlag(false);


	//エネミーのモデルをNewGO
	m_enemyModel = NewGO<prefab::ModelRender>(0);
	//モデルの各種設定
	m_enemyModel->SetTkmFilePath("Assets/modelData/soldier_bs01.tkm");
	m_enemyModel->SetVSEntryPoint("VSMainSkin");
	m_enemyModel->SetSkeleton(m_skeleton);
	m_scale *= 0.8f;
	m_enemyModel->SetScale(m_scale);
	m_enemyModel->SetShadowRecieverFlag(true);

	//スケルトンとアニメーションの初期化
	m_skeleton.Init("Assets/modelData/soldier_bs01.tks");
	m_skeleton.Update(Matrix::Identity);
	m_animation.Init(m_skeleton, m_animClip, 5);
	m_animation.Play(0);

	return true;
}

void Enemy::Update()
{
	float DeltaTime = g_gameTime.GetFrameDeltaTime();
	Vector3 footStepValue = Vector3::Zero;
	//アニメーションからfootstepの移動量を持ってくる
	footStepValue = m_animation.Update(DeltaTime);
	//Maxとは軸が違うので軸を合わせる
	float value = footStepValue.y;
	footStepValue.y = footStepValue.z;
	footStepValue.z = -value;
	footStepValue.y = -1.0f;
	footStepValue *= 24;

	Vector3 returnPos = characon.Execute(footStepValue, DeltaTime);
	m_pos = returnPos;

	m_enemyModel->SetPosition(m_pos);
	m_enemyModel->SetRotation(m_rot);

}