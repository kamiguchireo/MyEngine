#include "stdafx.h"
#include "Player.h"
#include "Game/Camera/GameCamera.h"
#include "IPlayer.h"
#include "PlayerStateIdle.h"
#include "PlayerStateMove.h"
#include "PlayerStateAim.h"
#include "PlayerHitBox.h"
#include "Game/Game.h"

Player* Player::m_Instance = nullptr;
Player::Player()
{
	m_Instance = this;
}

Player::~Player()
{

}

void Player::Destroy()
{
	//解放処理
	if (m_playerModel != nullptr)
	{
		DeleteGO(m_playerModel);
		m_playerModel = nullptr;
	}
	//カメラ
	if (m_camera != nullptr)
	{
		DeleteGO(m_camera);
		m_camera = nullptr;
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
	//エイムステート
	if (m_stateAim != nullptr)
	{
		delete m_stateAim;
		m_stateAim = nullptr;
	}
	//武器
	if (m_PlayerWeapon != nullptr)
	{
		DeleteGO(m_PlayerWeapon);
		m_PlayerWeapon = nullptr;
	}
	//スプライト
	if (m_AimFramesprite != nullptr)
	{
		DeleteGO(m_AimFramesprite);
		m_AimFramesprite = nullptr;
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
	if (m_HoldRifleSound != nullptr)
	{
		DeleteGO(m_HoldRifleSound);
		m_HoldRifleSound = nullptr;
	}
}

bool Player::Start()
{
	//プレイヤーのステータス
	m_Status = std::make_unique<PlayerStatus>(this);

	//ステートをnew
	m_stateIdle = new PlayerStateIdle(this);
	m_stateMove = new PlayerStateMove(this);
	m_stateAim = new PlayerStateAim(this);
	characon = new CharacterController();
	//待機ステートに切り替える
	ChangeState(m_stateIdle);

	m_camera = NewGO<GameCamera>(0, nullptr);

	characon->Init(15.0f,115.0f, m_pos);

	characon->GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Player);

	//待機状態のアニメーション
	m_animClip[enPlayerAnimation_Rifle_Idle].Load("Assets/animData/Rifle_Idle.tka");
	m_animClip[enPlayerAnimation_Rifle_Idle].SetLoopFlag(true);
	//歩き状態のアニメーション
	m_animClip[enPlayerAnimation_Rifle_Walk].Load("Assets/animData/Rifle_Walk.tka");
	m_animClip[enPlayerAnimation_Rifle_Walk].SetLoopFlag(true);
	//走り状態のアニメーション
	m_animClip[enPlayerAnimation_Rifle_Run].Load("Assets/animData/Rifle_Run.tka");
	m_animClip[enPlayerAnimation_Rifle_Run].SetLoopFlag(true);
	//スプリント状態のアニメーション
	m_animClip[enPlayerAnimation_Rifle_Sprint].Load("Assets/animData/Rifle_Sprint.tka");
	m_animClip[enPlayerAnimation_Rifle_Sprint].SetLoopFlag(true);
	//エイム状態のアニメーション
	m_animClip[enPlayerAnimation_Rifle_Down_To_Aim].Load("Assets/animData/Rifle_Down_To_Aim.tka");
	m_animClip[enPlayerAnimation_Rifle_Down_To_Aim].SetLoopFlag(false);
	//発砲状態のアニメーション
	m_animClip[enPlayerAnimation_Rifle_fire].Load("Assets/animData/Rifle_fire.tka");
	m_animClip[enPlayerAnimation_Rifle_fire].SetLoopFlag(true);
	//死亡アニメーション
	m_animClip[enPlayerAnimation_Death_From_Front].Load("Assets/animData/Death_From_Front.tka");
	m_animClip[enPlayerAnimation_Death_From_Front].SetLoopFlag(false);

	//モデルをNew
	m_playerModel = NewGO<prefab::ModelRender>(1, nullptr);
	//ファイルパス
	m_playerModel->SetTkmFilePath("Assets/modelData/soldier_bs01.tkm");
	//頂点シェーダーのエントリーポイント
	m_playerModel->SetVSEntryPoint("VSMainSkin");
	//スケルトンをセット
	m_playerModel->SetSkeleton(m_skeleton);
	//スケールをセット
	m_playerModel->SetScale(m_scale);
	//シャドウレシーバーにする
	m_playerModel->SetShadowRecieverFlag(true);
	//ディザリングを適応する
	m_playerModel->SetDitherFlag(true);

	//スケルトンとアニメーションの初期化
	m_skeleton.Init("Assets/modelData/soldier_bs01.tks");

	//スケルトンのアップデート
	m_skeleton.Update(Matrix::Identity);

	//頭のボーン番号を取得
	m_HeadBoneNum = m_skeleton.FindBoneID(L"mixamorig:Head");
	//アニメーションを初期化
	m_animation.Init(m_skeleton, m_animClip, enPlayerAnimation_Num);
	m_animation.Play(enPlayerAnimation_Rifle_Idle);

	//武器をNew
	m_PlayerWeapon = NewGO <Weapon>(2);
	//武器を初期化
	m_PlayerWeapon->Init(&m_skeleton,true);

	//スプライトをNew
	m_AimFramesprite = NewGO<prefab::SpriteRender>(3, nullptr);
	//初期化
	m_AimFramesprite->Init("Assets/Image/AimFrame.dds", 100, 100);

	m_HitBox = NewGO<PlayerHitBox>(4, nullptr);
	m_HitBox->Init(&m_skeleton, this);

	m_HoldRifleSound = NewGO<SoundSource>(5);
	m_HoldRifleSound->Init(L"Assets/sound/Hold_the_rifle.wav");
	m_HoldRifleSound->SetVolume(1.0f);
	//エイムステートの初期化
	m_stateAim->Init();

	return true;
}

void Player::Move()
{
	//左スティックが入力されているとき
	if (g_pad[0]->GetLStickXF() != 0.0f || g_pad[0]->GetLStickYF() != 0.0f)
	{
		//ステートをm_stateMoveに変更
		ChangeState(m_stateMove);
	}
}

void Player::AxisTrans()
{
	//Maxとは軸が違うので軸を合わせる
	float value = footStepValue.y;
	footStepValue.y = footStepValue.z;
	footStepValue.z = -value;
}

void Player::Hold()
{
	if (IsRightClick)
	{
		if (!GetAsyncKeyState(VK_RBUTTON))
		{
			IsRightClick = false;
			if (IsAim == false)
			{
				//ライフルを構える音を出す
				m_HoldRifleSound->Play(false,false);
				IsAim = true;
			}
			else
			{
				IsAim = false;
			}
		}
	}
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		IsRightClick = true;
	}
	if (IsAim == true)
	{
		//照準のαを1にする
		m_AimFramesprite->SetAlpha(1.0f);
		//エイムカメラに切り替え
		m_camera->SetCameraState(CameraState::AIM);
		ChangeState(m_stateAim);
	}
	else
	{
		m_HoldRifleSound->Stop();
		//照準のαを0にする
		m_AimFramesprite->SetAlpha(0.0f);
		//TPSカメラに切り替え
		m_camera->SetCameraState(CameraState::TPS);
	}
}

void Player::DeadProcess()
{
	//既に死んでいる場合
	if (m_animation.IsPlaying())
	{
		//アニメーションが終わっていない場合
		//死亡時のアニメーションを流す
		m_animation.Play(enPlayerAnimation_Death_From_Front);
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
	}
	else
	{
		auto g_game = Game::GetInstance();
		g_game->SceneTrans();
	}
}
void Player::Update()
{
	if (IsDead)
	{
		//プレイヤーが死亡した時
		DeadProcess();
		return;
	}
	//待機ステートに切り替える
	ChangeState(m_stateIdle);
	
	//1フレームにかかった時間を取得
	float DeltaTime = g_gameTime.GetFrameDeltaTime();
	//アニメーションからfootstepの移動量を持ってくる
	footStepValue = m_animation.Update(DeltaTime);
	
	AxisTrans();
	
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

	//移動に重力を加算
	footStepValue += m_gravity;

	//移動の処理
	Move();

	//構える処理
	Hold();

	//現在のステートの更新
	currentState->Update();
	//footStepValueに回転を適用
	m_rot.Apply(footStepValue);

	//キャラコンの計算
	Vector3 returnPos = characon->Execute(footStepValue);
	//ポジションに計算で帰ってきた値を代入
	m_pos = returnPos;

	//カメラのターゲットをセット
	m_camera->SetPivotPos(m_pos);
	m_camera->SetHeadPos(m_skeleton.GetBone(m_HeadBoneNum)->GetPosition());
	//ポジションをセット
	m_playerModel->SetPosition(m_pos);
	//回転をセット
	m_playerModel->SetRotation(m_rot);
	characon->GetRigidBody()->GetBody()->getUserIndex();
}