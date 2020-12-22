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

	void AddPosition(Vector3 pos)
	{
		m_pos += pos;
	}

	void PlayAnimation(int i)
	{
		m_animation.Play(i,0.3f);
	}

	void SetRotation(const Quaternion& rot)
	{
		m_rot = rot;
	}

	Vector3 GetForward()
	{
		return m_forward;
	}
private:
	void ChangeState(IPlayer* state);
private:
	IPlayer* currentState = nullptr;		//現在のステート
	prefab::ModelRender* m_playerModel = nullptr;		//プレイヤーのモデル
	Skeleton m_skeleton;
	Engine::Animation m_animation;
	Engine::AnimationClip m_animClip[4];
	Vector3 m_pos = {0.0f,0.0f,-1700.0f};
	Vector3 m_scale = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;
	PlayerStateIdle* m_stateIdle = nullptr;
	PlayerStateMove* m_stateMove = nullptr;
	GameCamera* m_camera = nullptr;
	Vector3 m_forward = Vector3::AxisZ;
};
