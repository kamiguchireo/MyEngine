#pragma once
#include "Player/Player.h"
#include "Enemy/Enemy.h"

class Test:public IGameObject
{
public:
	Test();
	~Test();

	void OnDestroy();
	bool Start();
	void Update();
private:
	Vector3 m_pos = { 0.0f,0.0f,0.0f };
	prefab::ModelRender* m_player = nullptr;
	Skeleton m_skeleton;
	AnimationClip m_animClip[1];
	Animation m_anim;
	Vector3 m_forward = Vector3::Front;
	Quaternion m_rot = Quaternion::Identity;
	float rot = 0.0f;
	Vector3 m_DeadAfterCameraPos = Vector3::Zero;
	Vector3 m_LerpForwardCameraPos = Vector3::Zero;
	Vector3 m_DeadAfterCameraTarget = Vector3::Zero;
	const float m_DeadCameraDist = 200.0f;
	float m_DeadAfterLeapSpeed = 0.2f;
	float m_DeadLeapTime = 0.0f;
};