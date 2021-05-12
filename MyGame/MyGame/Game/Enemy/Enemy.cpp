#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	//エネミーのステータス
	m_Status = std::make_unique<EnemyStatus>(this);

	//ステートをnew
	m_stateIdle = new EnemyStateIdle(this);
	m_stateMove = new EnemyStateMove(this);
	m_stateAim = new EnemyStateAim(this);
	characon = new CharacterController();
	ChangeState(m_stateIdle);

	m_path = Path::GetInstance();
	if (m_path != nullptr)
	{
		m_PassPos = m_path->GetPosition();
	}
	else
	{
		m_PassPos.push_back(m_pos);
		m_PassPos.push_back(Vector3{ 300.0f,0.0f,100.0f });
		m_PassPos.push_back(Vector3{ 100.0f,0.0f,100.0f });
		m_PassPos.push_back(Vector3{ 100.0f,0.0f,-1000.0f });

	}

	m_PassSize = static_cast<int>(m_PassPos.size()) - 1;
}

Enemy::~Enemy()
{
	//モデルレンダー
	if (m_enemyModel != nullptr)
	{
		DeleteGO(m_enemyModel);
		m_enemyModel = nullptr;
	}
	//待機ステート
	if (m_stateIdle != nullptr)
	{
		delete m_stateIdle;
		m_stateIdle = nullptr;
	}
	//移動ステート
	if (m_stateMove != nullptr)
	{
		delete m_stateMove;
		m_stateMove = nullptr;
	}
	if (m_stateAim != nullptr)
	{
		delete m_stateAim;
		m_stateMove = nullptr;
	}
	//武器
	if (m_weapon != nullptr)
	{
		DeleteGO(m_weapon);
		m_weapon = nullptr;
	}
	//ヒットボックス
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
}



bool Enemy::Start()
{
	//ポジションをパスの0番目に合わせる
	if (m_PassPos.size() >= 1)
	{
		m_pos = m_PassPos[0];
	}
	//キャラコンの初期化
	characon->Init(15.0f, 115.0f, m_pos);

	//待機状態のアニメーション
	m_animClip[enEnemyAnimation_Rifle_Idle].Load("Assets/animData/Rifle_Idle.tka");
	m_animClip[enEnemyAnimation_Rifle_Idle].SetLoopFlag(true);
	//歩き状態のアニメーション
	m_animClip[enEnemyAnimation_Rifle_Walk].Load("Assets/animData/Rifle_Walk.tka");
	m_animClip[enEnemyAnimation_Rifle_Walk].SetLoopFlag(true);
	//走り状態のアニメーション
	m_animClip[enEnemyAnimation_Rifle_Run].Load("Assets/animData/Rifle_Run.tka");
	m_animClip[enEnemyAnimation_Rifle_Run].SetLoopFlag(true);
	//スプリント状態のアニメーション
	m_animClip[enEnemyAnimation_Rifle_Sprint].Load("Assets/animData/Rifle_Sprint.tka");
	m_animClip[enEnemyAnimation_Rifle_Sprint].SetLoopFlag(true);
	//エイム状態のアニメーション
	m_animClip[enEnemyAnimation_Rifle_Down_To_Aim].Load("Assets/animData/Rifle_Down_To_Aim.tka");
	m_animClip[enEnemyAnimation_Rifle_Down_To_Aim].SetLoopFlag(false);
	//死亡時のアニメーション
	m_animClip[enEnemyAnimation_Death_From_Front].Load("Assets/animData/Death_From_Front.tka");
	m_animClip[enEnemyAnimation_Death_From_Front].SetLoopFlag(false);

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
	m_animation.Init(m_skeleton, m_animClip, enEnemyAnimation_Num);
	m_animation.Play(enEnemyAnimation_Rifle_Idle);
	m_rot.SetRotationDegY(0.0f);

	//武器のNewGOとInit
	m_weapon = NewGO<Weapon>(1);
	m_weapon->Init(&m_skeleton);

	m_HitBox = NewGO<EnemyHitBox>(2);
	m_HitBox->Init(&m_skeleton, this);

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

void Enemy::Update()
{
	if (IsDead == true)
	{
		m_animation.Play(enEnemyAnimation_Death_From_Front);
		float DeltaTime = g_gameTime.GetFrameDeltaTime();
		m_animation.Update(DeltaTime);
		return;
	}
	if (CurrentPass == NextPass)
	{
		//その場で停止する
		IsStop = true;
		//待機ステートに変更
		ChangeState(m_stateIdle);
		//次のパスを変更
		ChangeNextPass();
	}
	if (IsStop == false)
	{
		ChangeState(m_stateMove);
	}

	//次のパスへのベクトル
	Vector3 moveVec = m_PassPos[NextPass] - m_pos;
	//次のパスへの距離が一定以内なら
	if (moveVec.Length() <= PassDist)
	{
		//目的地の着いたので
		//現在のパスを変更
		CurrentPass = NextPass;
	}

	//次のパスへのベクトル
	moveVec.y = 0.0f;
	moveVec.Normalize();
	
	//次のパスへ向かう回転
	m_rot.SetRotation(Vector3::AxisZ, moveVec);

	float DeltaTime = g_gameTime.GetFrameDeltaTime();
	Vector3 footStepValue = Vector3::Zero;

	static float i = 0;
	i += DeltaTime;
	if (i > 10.0f)
	{
		m_Status->Damage(100);
	}

	//アニメーションからfootstepの移動量を持ってくる
	footStepValue = m_animation.Update(DeltaTime);

	//Maxとは軸が違うので軸を合わせる
	float value = footStepValue.y;
	footStepValue.y = footStepValue.z;
	footStepValue.z = -value;
	//フットステップを調整
	footStepValue *= footStepAdjustValue;
	
	//重力を加算
	if (characon->IsOnGround())
	{
		//地面上にいるときは重力をリセット
		m_gravity *= 0.0f;
	}
	else
	{
		//空中にいるときは重力を加算し続ける
		m_gravity += gravity;
	}

	footStepValue += m_gravity;

	//現在のステートの更新
	currentState->Update();

	//footStepに回転を適応
	m_rot.Apply(footStepValue);

	//キャラコンの計算
	Vector3 returnPos = characon->Execute(footStepValue, DeltaTime);

	m_pos = returnPos;
	
	m_enemyModel->SetPosition(m_pos);
	m_enemyModel->SetRotation(m_rot);

	if (IsDead == true)
	{
		delete characon;
		characon = nullptr;
	}
}