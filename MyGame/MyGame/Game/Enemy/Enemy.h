#pragma once
#include "EnemyStatus.h"

class GameCamera;
class Path;
class Weapon;
class EnemyHitBox;
class IEnemy;
class EnemyStateIdle;
class EnemyStateMove;
class EnemyStateAim;
class EnemyStatus;
class Player;
class EnemyRayTest;

enum EnemyActState {
	enState_Normal,
	enState_vigilant,
	enState_Discover
};

class Enemy:public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();
	void UpdateAnimation(float f)
	{
		m_animation.Update(f);
	}
	//アニメーションを再生
	void PlayAnimation(int i)
	{
		m_animation.Play(i, 0.3f);
	}

	void SetIsStop(bool flag)
	{
		IsStop = flag;
	}

	//死亡
	void Dead()
	{
		IsDead = true;
	}

	//ダメージを受ける
	void Damage(int i)
	{
		m_Status->Damage(i);
	}
	//プレイヤーを見ることができるか
	bool CanSeePlayer();

	Vector3& GetPosition()
	{
		return m_pos;
	}

	void ChangeActState(EnemyActState state)
	{
		m_ActState = state;
	}

private:
	//次のパスへ変更
	void ChangeNextPass();
	//ステートの変更
	//state		ステート
	void ChangeState(IEnemy* state)
	{
		currentState = state;
	}
private:
	IEnemy* currentState = nullptr;		//現在のステート
	prefab::ModelRender* m_enemyModel = nullptr;		//エネミーのモデル
	Skeleton m_skeleton;
	Engine::Animation m_animation;		//アニメーション
	Engine::AnimationClip m_animClip[enEnemyAnimation_Num];		//アニメーションクリップ
	Vector3 m_pos = { 0.0f,10.0f,-100.0f };		//ポジション
	Vector3 m_scale = Vector3::One;		//拡大率
	Quaternion m_rot = Quaternion::Identity;		//回転率
	CharacterController* characon = nullptr;
	float rot = 0.0f;
	Path* m_path = nullptr;		//パス
	std::vector<Vector3> m_PassPos;
	int m_PassSize = 0;		//パスを入れている配列のサイズ
	int CurrentPass = 0;		//現在のパス
	int NextPass = 0;		//次のパス
	Weapon* m_weapon = nullptr;
	EnemyHitBox* m_HitBox = nullptr;
	EnemyStateIdle* m_stateIdle = nullptr;		//待機状態
	EnemyStateMove* m_stateMove = nullptr;		//移動状態
	EnemyStateAim* m_stateAim = nullptr;		//エイム状態
	bool IsStop = false;		//止まっているかどうか
	Vector3 m_gravity = Vector3::Zero;		//重力による加速
	const float PassDist = 10.0f;		//パスの範囲
	std::unique_ptr<EnemyStatus> m_Status = nullptr;
	bool IsDead = false;		//死んでいるかどうか
	Player* m_player = nullptr;
	float ToPlayerAngle = 0.0f;
	Vector3 ToPlayer = Vector3::Zero;
	const float RotateSpeed = 1.0f;
	float RayWaitTime = 5.0f;
	std::unique_ptr<EnemyRayTest> m_RayTest = nullptr;
	Vector3 m_moveVec = Vector3::Zero;
	EnemyActState m_ActState = EnemyActState::enState_Normal;
	Vector3 LastPlayerPos = Vector3::Zero;
	const float EnemyAngle = 70.0f;
};