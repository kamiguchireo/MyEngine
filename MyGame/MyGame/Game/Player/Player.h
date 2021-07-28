#pragma once
#include "SourceFile/Physics/CharacterController.h"
#include "Game/Weapon.h"
#include "SourceFile/Graphic/SpriteRender.h"
#include "PlayerStatus.h"
#include "SourceFile/sound/SoundSource.h"
#include "Game/Camera/GameCamera.h"

class IPlayer;
class GameCamera;
class PlayerStateIdle;
class PlayerStateMove;
class PlayerStateAim;
class PlayerHitBox;
class Player:public IGameObject
{
public:
	Player();
	~Player();

	void OnDestroy();
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

	//アニメーションを更新
	void UpdateAnimation(float f)
	{
		m_animation.Update(f);
	}

	//ポジションをセット
	void SetPosition(const Vector3& pos)
	{
		m_pos = pos;
	}
	//回転をセット
	void SetRotation(const Quaternion& rot)
	{
		m_rot = rot;
	}
	//スケールをセット
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	//正面をゲット
	Vector3 GetForward()const
	{
		return m_forward;
	}

	//正面をセット
	void SetForward(Vector3 vec)
	{
		m_forward = vec;
	}
	//右方向をセット
	void SetRight(Vector3 vec)
	{
		m_right = vec;
	}
	//武器用の行列をゲット
	const Matrix& GetWeaponBoneMat()
	{
		return m_skeleton.GetWeaponMatrix();
	}

	//デカールを追加
	bool Shooting()
	{
		if (m_PlayerWeapon != nullptr)
		{
			Vector3 Direction = g_camera3D->GetTarget() - g_camera3D->GetPosition();
			Direction.Normalize();
			auto bone = m_skeleton.GetBone(m_skeleton.GetWeaponBoneNum());
			Vector3 weaponpos = bone->GetPosition();
			Vector3 CameraToWeaponPos = g_camera3D->GetPosition() - weaponpos;
			float length = CameraToWeaponPos.Length();
			Vector3 pos = g_camera3D->GetPosition();
			pos += Direction * length;
			m_PlayerWeapon->SetRay(pos, Direction);
			return m_PlayerWeapon->shooting();
		}
		return false;
	}

	bool IsWeaponAvailable()
	{
		return m_PlayerWeapon->IsAvailable();
	}

	void WeaponRelease()
	{
		m_PlayerWeapon->Release();
	}
	//死亡
	void Dead()
	{
		//死亡時のアニメーションを流す
		m_animation.Play(enPlayerAnimation_Death_From_Front);
		IsDead = true;
	}

	//ダメージを受ける
	void Damage(int i)
	{
		m_Status->Damage(i);
	}

	//スケルトンをゲット
	Skeleton* GetSkeleton()
	{
		return &m_skeleton;
	}

	//シングルトン
	static Player* GetInstance()
	{
		if (m_Instance != nullptr)
		{
			return m_Instance;
		}
		return nullptr;
	}
	const Vector3 GetPosition()const
	{
		return m_pos;
	}

	void ChangeCameraStateTPS()
	{
		m_camera->SetCameraState(CameraState::TPS);
	}
private:
	//ステートの変更
	//state		ステート
	void ChangeState(IPlayer* state)
	{
		currentState = state;
	}
	
	//移動の処理
	void Move();

	//軸変換
	void AxisTrans();

	//構える処理
	void Hold();

	//死亡時の処理
	void DeadProcess();

private:
	static Player* m_Instance;		//インスタンス
	IPlayer* currentState = nullptr;		//現在のステート
	prefab::ModelRender* m_playerModel = nullptr;		//プレイヤーのモデル
	Skeleton m_skeleton;		//スケルトン
	Engine::Animation m_animation;		//アニメーション
	Engine::AnimationClip m_animClip[enPlayerAnimation_Num];		//アニメーションクリップ
	Vector3 m_pos = {0.0f,50.0f,-1700.0f};		//ポジション
	Vector3 m_scale = { 0.8f,0.8f,0.8f };		//スケール
	Quaternion m_rot = Quaternion::Identity;		//キャラクターの回転
	PlayerStateIdle* m_stateIdle = nullptr;		//待機状態
	PlayerStateMove* m_stateMove = nullptr;		//移動状態
	PlayerStateAim* m_stateAim = nullptr;		//エイム状態
	Weapon* m_PlayerWeapon = nullptr;		//プレイヤーの武器
	GameCamera* m_camera = nullptr;		//カメラ
	Vector3 m_forward = Vector3::Front;		//前方向
	Vector3 m_right = Vector3::Right;		//右方向
	CharacterController* characon = nullptr;		//キャラコン
	Vector3 footStepValue = Vector3::Zero;		//footStepの移動量
	prefab::SpriteRender* m_AimFramesprite = nullptr;		//エイム時に表示するスプライト
	Vector3 m_gravity = Vector3::Zero;		//重力による加速
	PlayerHitBox* m_HitBox = nullptr;
	bool IsDead = false;		//死んでいるかどうか
	int m_HeadBoneNum = -1;
	std::unique_ptr<PlayerStatus> m_Status = nullptr;
	SoundSource* m_HoldRifleSound = nullptr;		//銃を構えるときのサウンド
	bool IsRightClick = false;
	bool IsAim = false;

};