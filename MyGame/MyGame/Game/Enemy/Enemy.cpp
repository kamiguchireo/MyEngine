#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	m_path = Path::GetInstance();
	if (m_path != nullptr)
	{
		m_position = m_path->GetPosition();
	}
	else
	{
		m_position.push_back(m_pos);
		m_position.push_back(Vector3{ 100.0f,0.0f,0.0f });
	}

	m_PassSize = m_position.size() - 1;
}

Enemy::~Enemy()
{

	if (m_enemyModel != nullptr)
	{
		DeleteGO(m_enemyModel);
		m_enemyModel = nullptr;
	}
	if (m_camera != nullptr)
	{
		DeleteGO(m_camera);
		m_camera = nullptr;
	}
	if (m_weapon != nullptr)
	{
		DeleteGO(m_weapon);
		m_weapon = nullptr;
	}
}

bool Enemy::Start()
{
	//m_camera = NewGO<GameCamera>(0, nullptr);

	//ポジションをパスの0番目に合わせる
	if (m_position.size() >= 1)
	{
		m_pos = m_position[0];
	}
	//キャラコンの初期化
	characon.Init(15.0f, 115.0f, m_pos);

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
	m_rot.SetRotationDegY(0.0f);

	//武器のNewGOとInit
	m_weapon = NewGO<Weapon>(1);
	m_weapon->Init(&m_skeleton);

	return true;
}

void Enemy::ChangeNextPass()
{
	if (NextPass < m_PassSize)
	{
		NextPass++;
	}
	else
	{
		NextPass = 0;
	}
}
void Enemy::StopPass()
{
	static float f = 5.0f;
	f -= g_gameTime.GetFrameDeltaTime();
	m_animation.Play(0);
	if (f <= 0.0f)
	{
		ChangeNextPass();
		f = 2.5f;
	}
}

void Enemy::Update()
{
	m_animation.Play(1);

	if (CurrentPass == NextPass)
	{
		StopPass();
	}
	//次のポジションを設定
	Vector3 NextPosition = m_position[NextPass];
	//Vector3 NextPosition = Vector3::Zero;
	if (m_pos.x > NextPosition.x - 10.0f && m_pos.x < NextPosition.x + 10.0f)
	{
		if (m_pos.z > NextPosition.z - 10.0f && m_pos.z < NextPosition.z + 10.0f)
		{
			CurrentPass = NextPass;
		}
	}
	Vector3 moveVec = NextPosition - m_pos;
	moveVec.Normalize();
	m_rot.SetRotation(Vector3::AxisZ, moveVec);
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

	m_rot.Apply(footStepValue);

	Vector3 returnPos = characon.Execute(footStepValue, DeltaTime);
	Vector3 move_vec = returnPos - m_pos;

	m_pos = returnPos;

	//m_camera->SetTarget(m_pos);

	m_enemyModel->SetPosition(m_pos);
	m_enemyModel->SetRotation(m_rot);

}