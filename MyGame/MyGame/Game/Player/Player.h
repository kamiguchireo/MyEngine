#pragma once
#include "IPlayer.h"
#include "PlayerStateIdle.h"
#include "PlayerStateMove.h"
#include "Game/Camera/GameCamera.h"
#include "Game/Weapon.h"
#include "PlayerStateAim.h"
#include "SourceFile/Physics/CharacterController.h"

class Player:public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

	//�|�W�V���������Z
	void AddPosition(Vector3 pos)
	{
		m_pos += pos;
	}

	//�A�j���[�V�������Đ�
	void PlayAnimation(int i)
	{
		m_animation.Play(i,0.3f);
	}

	//��]���Z�b�g
	void SetRotation(const Quaternion& rot)
	{
		m_rot = rot;
	}

	//���ʂ��Q�b�g
	Vector3 GetForward()const
	{
		return m_forward;
	}

	//����p�̍s����Q�b�g
	const Matrix& GetWeaponBoneMat()
	{
		return m_skeleton.GetWeaponMatrix();
	}

	//�f�J�[����ǉ�
	void AddDecale()
	{
		if (m_PlayerWeapon != nullptr)
		{
			m_PlayerWeapon->AddDecale();
		}
	}
private:
	void ChangeState(IPlayer* state);
private:
	IPlayer* currentState = nullptr;		//���݂̃X�e�[�g
	prefab::ModelRender* m_playerModel = nullptr;		//�v���C���[�̃��f��
	Skeleton m_skeleton;
	Engine::Animation m_animation;
	Engine::AnimationClip m_animClip[enPlayerAnimation_Num];
	Vector3 m_pos = {0.0f,10.0f,-1700.0f};
	Vector3 m_scale = { 0.8f,0.8f,0.8f };
	Quaternion m_rot = Quaternion::Identity;
	PlayerStateIdle* m_stateIdle = nullptr;
	PlayerStateMove* m_stateMove = nullptr;
	PlayerStateAim* m_stateAim = nullptr;
	Weapon* m_PlayerWeapon = nullptr;
	GameCamera* m_camera = nullptr;
	Vector3 m_forward = Vector3::AxisZ;
	CharacterController characon;
};