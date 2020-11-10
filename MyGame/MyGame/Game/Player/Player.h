#pragma once
#include "IPlayer.h"
#include "PlayerStateIdle.h"

class Player:public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Draw();

private:
	void ChangeState(IPlayer* state);
private:
	IPlayer* currentState = nullptr;		//���݂̃X�e�[�g
	prefab::ModelRender* m_playerModel = nullptr;		//�v���C���[�̃��f��
	Skeleton m_skeleton;
	Engine::Animation m_animation;
	Engine::AnimationClip m_animClip[1];
	Vector3 m_pos = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;
	PlayerStateIdle m_stateIdle;
};
