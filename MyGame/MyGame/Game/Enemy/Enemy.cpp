#include "stdafx.h"
#include "Enemy.h"
#include "SourceFile/Physics/CharacterController.h"
#include "Game/Camera/GameCamera.h"
#include "Game/Stage/Path.h"
#include "Game/Weapon.h"
#include "EnemyHitBox.h"
#include "IEnemy.h"
#include "EnemyStateIdle.h"
#include "EnemyStateMove.h"
#include "EnemyStateAim.h"
#include "Game/Player/Player.h"
#include "EnemyRayTest.h"
#include <random>

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::OnDestroy()
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
		m_stateAim = nullptr;
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
	//エネミーのステータス
	m_Status = std::make_unique<EnemyStatus>(this);

	//ステートをnew
	m_stateIdle = new EnemyStateIdle(this);
	m_stateMove = new EnemyStateMove(this);
	m_stateAim = new EnemyStateAim(this);
	characon = new CharacterController();
	ChangeState(m_stateIdle);

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

	m_RayTest = std::make_unique<EnemyRayTest>(this);

	//プレイヤーのインスタンスを取得
	m_player = Player::GetInstance();

	//ポジションをパスの0番目に合わせる
	if (m_PassPos.size() >= 1)
	{
		m_pos = m_PassPos[0];
	}
	//キャラコンの初期化
	characon->Init(15.0f, 115.0f, m_pos);
	characon->GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Enemy);

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

	//乱数の種の変更
	std::random_device rnd;
	srand(rnd());

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

bool Enemy::CanSeePlayer()
{
	//互いに大きさ1のベクトルなので内積をするとcosθが残る
	ToPlayerAngle = Dot(ToPlayer, m_moveVec);
	//cosから角度を求める
	ToPlayerAngle = acosf(ToPlayerAngle);
	//ラジアン単位からディグリー単位に変換
	ToPlayerAngle = Math::RadToDeg(ToPlayerAngle);
	//角度が70度以下の時
	if (ToPlayerAngle <= EnemyAngle)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::DeadProcess()
{
	//既に死んでいる場合
	if (m_animation.IsPlaying())
	{
		//アニメーションが終わっていない場合
		//死亡時のアニメーションを流す
		m_animation.Play(enEnemyAnimation_Death_From_Front);
		m_animation.Update(g_gameTime.GetFrameDeltaTime());
		//ヒットボックスが残っているとき削除
		if (m_HitBox != nullptr)
		{
			DeleteGO(m_HitBox);
			m_HitBox = nullptr;
		}
		//キャラコンが残っているとき削除
		if (characon != nullptr)
		{
			delete characon;
			characon = nullptr;
		}
		//m_weapon->StopFireSound();
	}
}

void Enemy::Update()
{
	if (IsDead == true)
	{
		//死亡時の処理
		DeadProcess();
		return;
	}

	float DeltaTime = g_gameTime.GetFrameDeltaTime();

	//プレイヤーへの方向
	ToPlayer = m_player->GetPosition() - m_pos;
	float ToPlayerLength = ToPlayer.Length();
	ToPlayer.Normalize();

	//レイテストをアップデート
	if (ToPlayerLength <= 3000.0f)
	{
		m_RayTest->Update(m_player->GetPosition());
	}

	//プレイヤーを発見しているとき
	if (m_ActState == EnemyActState::enState_Discover)
	{
		//時間を加算
		NowTime_Rand += DeltaTime;
		if (NowTime_Rand >= WaitTime_Rand)
		{	
			//一定時間たつと
			if (RandRange >= RandRangeMin)
			{
				//最低値より値が大きい場合に減算する
				RandRange -= ChangeRandRange;
				NowTime_Rand = 0.0f;
			}
		}
		//プレイヤーの方向へ向ける
		//最後にプレイヤーを見た場所を更新
		LastPlayerPos = m_player->GetPosition();
		m_moveVec = LastPlayerPos - m_pos;
		m_moveVec.Normalize();
		m_animation.Play(enEnemyAnimation_Rifle_Idle,0.3f);

		//武器のポジションをとってくる
		Vector3 WeaponPos = m_skeleton.GetBone(m_skeleton.GetWeaponBoneNum())->GetPosition();
		//武器のポジションだと自分にレイが当たってしまうので少し前に出す
		WeaponPos += ToPlayer * 25.0f;

		int AddRandPos = rand();
		//プレイヤーに加算する値がプラスかマイナスか決める
		int RandDir = rand();
		//範囲を決める
		AddRandPos %= RandRange;
		//0か1の2択にする
		RandDir %= 2;

		float AddPlayerPos[3] = { 0.0f };
		for (int i = 0; i < 3; i++)
		{
			if (RandDir == 0)
			{
				AddPlayerPos[i] = AddRandPos;
			}
			else
			{
				AddPlayerPos[i] = -AddRandPos;
			}
		}
		Vector3 ToPlayerRand = Vector3::Zero;
		ToPlayerRand = m_player->GetPosition();
		ToPlayerRand.x += AddPlayerPos[0];
		ToPlayerRand.y += AddPlayerPos[1];
		ToPlayerRand.z += AddPlayerPos[2];

		ToPlayerRand -= m_pos;
		ToPlayerRand.Normalize();
		//レイの始点と方向をセット
		m_weapon->SetRay(WeaponPos, ToPlayerRand);
		//射撃
		m_weapon->shooting();
	}
	else if (m_ActState == EnemyActState::enState_vigilant)
	{
		//最後にプレイヤーを見た場所に移動
		m_moveVec = LastPlayerPos - m_pos;
		m_moveVec.Normalize();
	}
	else
	{
		//m_weapon->StopFireSound();
		//時間を加算
		NowTime_Rand += DeltaTime;
		if (NowTime_Rand >= WaitTime_Rand)
		{
			//一定時間たつと
			if (RandRange <= RandRangeMax)
			{
				//最低値より値が大きい場合に減算する
				RandRange += ChangeRandRange;
				NowTime_Rand = 0.0f;
			}
		}

		//次のパスへのベクトル
		m_moveVec = m_PassPos[NextPass] - m_pos;
		//次のパスへの距離が一定以内なら
		if (m_moveVec.Length() <= PassDist)
		{
			//目的地の着いたので
			//現在のパスを変更
			CurrentPass = NextPass;
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
		m_moveVec.y = 0.0f;
		m_moveVec.Normalize();
	}

	//回転を適用
	m_rot.SetRotation(Vector3::AxisZ, m_moveVec);

	//アニメーションからfootstepの移動量を持ってくる
	footStepValue = m_animation.Update(DeltaTime);

	//Maxとは軸が違うので軸を合わせる
	float value = footStepValue.y;
	footStepValue.y = footStepValue.z;
	footStepValue.z = -value;

	//フットステップを調整
	//スケールの値をとる
	footStepValue *= m_scale.x;

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
	if (m_ActState == EnemyActState::enState_Normal)
	{
		currentState->Update();
	}

	//footStepに回転を適応
	m_rot.Apply(footStepValue);

	//キャラコンの計算
	Vector3 returnPos = characon->Execute(footStepValue);

	m_pos = returnPos;

	m_enemyModel->SetPosition(m_pos);
	m_enemyModel->SetRotation(m_rot);
}