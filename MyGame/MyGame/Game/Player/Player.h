#pragma once
#include "IPlayer.h"
#include "PlayerStateIdle.h"
#include "PlayerStateMove.h"
#include "Game/Camera/GameCamera.h"
#include "Game/Weapon.h"
#include "PlayerStateAim.h"
#include "SourceFile/Physics/CharacterController.h"
#include "SourceFile/Graphic/SpriteRender.h"

class Player:public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

	//ポジションを加算
	void AddPosition(Vector3 pos)
	{
		m_pos += pos;
	}

	//アニメーションを再生
	void PlayAnimation(int i)
	{
		m_animation.Play(i,0.3f);
	}

	//回転をセット
	void SetRotation(const Quaternion& rot)
	{
		m_rot = rot;
	}

	//正面をゲット
	Vector3 GetForward()const
	{
		return m_forward;
	}

	//武器用の行列をゲット
	const Matrix& GetWeaponBoneMat()
	{
		return m_skeleton.GetWeaponMatrix();
	}

	//デカールを追加
	void AddDecale()
	{
		if (m_PlayerWeapon != nullptr)
		{
			m_PlayerWeapon->AddDecale();
		}
	}

private:
	//ステートの変更
	//state		ステート
	void ChangeState(IPlayer* state);
	
	//移動の処理
	void Move();

	//軸変換
	void AxisTrans();

	//構える処理
	void Hold();
private:
	IPlayer* currentState = nullptr;		//現在のステート
	prefab::ModelRender* m_playerModel = nullptr;		//プレイヤーのモデル
	Skeleton m_skeleton;		//スケルトン
	Engine::Animation m_animation;		//アニメーション
	Engine::AnimationClip m_animClip[enPlayerAnimation_Num];		//アニメーションクリップ
	Vector3 m_pos = {0.0f,10.0f,-1700.0f};		//ポジション
	Vector3 m_scale = { 0.8f,0.8f,0.8f };		//スケール
	Quaternion m_rot = Quaternion::Identity;		//キャラクターの回転
	PlayerStateIdle* m_stateIdle = nullptr;		//待機状態
	PlayerStateMove* m_stateMove = nullptr;		//移動状態
	PlayerStateAim* m_stateAim = nullptr;		//エイム状態
	Weapon* m_PlayerWeapon = nullptr;		//プレイヤーの武器
	GameCamera* m_camera = nullptr;		//カメラ
	Vector3 m_forward = Vector3::AxisZ;		//前方向
	CharacterController characon;		//キャラコン
	Vector3 footStepValue = Vector3::Zero;		//footStepの移動量
	prefab::SpriteRender* m_sprite = nullptr;
};