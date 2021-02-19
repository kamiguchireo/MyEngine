#pragma once
#include "SourceFile/graphic/ModelRender.h"
#include "SourceFile/Physics/CharacterController.h"
#include "Game/Camera/GameCamera.h"
#include "Game/Stage/Pass.h"

class Enemy:public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();

private:
	prefab::ModelRender* m_enemyModel = nullptr;		//エネミーのモデル
	Skeleton m_skeleton;
	Engine::Animation m_animation;		//アニメーション
	Engine::AnimationClip m_animClip[5];		//アニメーションクリップ
	Vector3 m_pos = { 0.0f,5.0f,-100.0f };		//ポジション
	Vector3 m_scale = Vector3::One;		//拡大率
	Quaternion m_rot = Quaternion::Identity;		//回転率
	CharacterController characon;
	GameCamera* m_camera = nullptr;
	float rot = 0.0f;
	Pass* m_pass = nullptr;		//パス
};