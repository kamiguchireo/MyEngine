#pragma once
#include "SourceFile/graphic/ModelRender.h"
#include "SourceFile/Physics/CharacterController.h"
#include "Game/Camera/GameCamera.h"
#include "Game/Stage/Path.h"
#include "Game/Weapon.h"
#include "EnemyHitBox.h"
#include "EnemyStateIdle.h"
#include "EnemyStateMove.h"
#include "EnemyStateAim.h"

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
private:
	//パスで停止する
	void StopPass();
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
	Engine::AnimationClip m_animClip[5];		//アニメーションクリップ
	Vector3 m_pos = { 0.0f,10.0f,-100.0f };		//ポジション
	Vector3 m_scale = Vector3::One;		//拡大率
	Quaternion m_rot = Quaternion::Identity;		//回転率
	CharacterController characon;
	float rot = 0.0f;
	Path* m_path = nullptr;		//パス
	std::vector<Vector3> m_position;
	int m_PassSize = 0;
	int CurrentPass = 0;		//現在のパス
	int NextPass = 0;		//次のパス
	Weapon* m_weapon = nullptr;
	//GameCamera* m_camera = nullptr;
	EnemyHitBox* m_HitBox = nullptr;
	EnemyStateIdle* m_stateIdle = nullptr;		//待機状態
	EnemyStateMove* m_stateMove = nullptr;		//移動状態
	EnemyStateAim* m_stateAim = nullptr;		//エイム状態
};