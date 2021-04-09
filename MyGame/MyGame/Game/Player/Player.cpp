#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//ステートをnew
	m_stateIdle = new PlayerStateIdle(this);
	m_stateMove = new PlayerStateMove(this);
	m_stateAim = new PlayerStateAim(this);
	//待機ステートに切り替える
	ChangeState(m_stateIdle);
}

Player::~Player()
{
	//解放処理
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
	if (m_PlayerWeapon != nullptr)
	{
		DeleteGO(m_PlayerWeapon);
		m_PlayerWeapon = nullptr;
	}
	if (m_sprite != nullptr)
	{
		DeleteGO(m_sprite);
		m_sprite = nullptr;
	}
}

void Player::ChangeState(IPlayer* state)
{
	currentState = state;
}

bool Player::Start()
{
	m_camera = NewGO<GameCamera>(0, nullptr);

	characon.Init(15.0f,115.0f, m_pos);
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

	//アニメーションを初期化
	m_animation.Init(m_skeleton, m_animClip, 6);
	m_animation.Play(0);

	//武器をNew
	m_PlayerWeapon = NewGO <Weapon>(2);
	//武器を初期化
	m_PlayerWeapon->Init(&m_skeleton,true);

	//スプライトをNew
	m_sprite = NewGO<prefab::SpriteRender>(3, nullptr);
	//初期化
	m_sprite->Init("Assets/Image/AimFrame.dds", 100.0f, 100.0f);

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
	//右クリックされたとき
	if (GetKeyState(VK_RBUTTON))
	{
		//エイムカメラに切り替え
		m_camera->SetCameraState(CameraState::AIM);
		ChangeState(m_stateAim);
		//カメラの前方向を取得
		Vector3 aimForward = g_camera3D->GetForward();
		//y成分は必要ないので0にする
		aimForward.y = 0.0f;
		//正規化
		aimForward.Normalize();
		//二つのベクトルに直行するベクトルを取得
		Vector3 Axis = Cross(Vector3::Front, aimForward);
		//正規化
		Axis.Normalize();
		//ベクトルの大きさ1なので二つのベクトルのcosθのみが残る
		float dot = Dot(Vector3::Front, aimForward);
		//プレイヤーを視点方向に回転
		m_rot.SetRotation(Axis, acosf(dot));
	}
	else
	{
		//TPSカメラに切り替え
		m_camera->SetCameraState(CameraState::TPS);
		Vector3 aimForward = g_camera3D->GetForward();
		aimForward.y = 0.0f;
	}
}

void Player::Update()
{
	//待機ステートに切り替える
	ChangeState(m_stateIdle);
	
	//1フレームにかかった時間を取得
	float DeltaTime = g_gameTime.GetFrameDeltaTime();
	//アニメーションからfootstepの移動量を持ってくる
	footStepValue = m_animation.Update(DeltaTime);
	
	AxisTrans();
	
	//フットステップを調整
	footStepValue *= footStepAdjustValue;

	//重力を加算
	footStepValue += gravity;

	//移動の処理
	Move();

	//構える処理
	Hold();

	currentState->Update();
	//footStepValueに回転を適用
	m_rot.Apply(footStepValue);
	//キャラコンの計算
	Vector3 returnPos = characon.Execute(footStepValue, DeltaTime);

	m_pos = returnPos;

	//カメラのターゲットをセット
	m_camera->SetTarget(m_pos);
	m_camera->SetPosition(m_pos);

	//ポジションをセット
	m_playerModel->SetPosition(m_pos);
	//回転をセット
	m_playerModel->SetRotation(m_rot);

}