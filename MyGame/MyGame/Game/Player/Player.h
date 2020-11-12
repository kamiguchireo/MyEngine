#pragma once
#include "IPlayer.h"
#include "PlayerStateIdle.h"
#include "PlayerStateMove.h"
#include "Game/Camera/GameCamera.h"

class Player:public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

private:
	void ChangeState(IPlayer* state);
private:
	IPlayer* currentState = nullptr;		//現在のステート
	prefab::ModelRender* m_playerModel = nullptr;		//プレイヤーのモデル
	Skeleton m_skeleton;
	Engine::Animation m_animation;
	Engine::AnimationClip m_animClip[2];
	Vector3 m_pos = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;
	PlayerStateIdle m_stateIdle;
	PlayerStateMove m_stateMove;
	GameCamera* m_camera = nullptr;
};
