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
	//�X�e�[�g�̕ύX
	//state		�X�e�[�g
	void ChangeState(IPlayer* state);
	
	//�ړ��̏���
	void Move();

	//���ϊ�
	void AxisTrans();

	//�\���鏈��
	void Hold();
private:
	IPlayer* currentState = nullptr;		//���݂̃X�e�[�g
	prefab::ModelRender* m_playerModel = nullptr;		//�v���C���[�̃��f��
	Skeleton m_skeleton;		//�X�P���g��
	Engine::Animation m_animation;		//�A�j���[�V����
	Engine::AnimationClip m_animClip[enPlayerAnimation_Num];		//�A�j���[�V�����N���b�v
	Vector3 m_pos = {0.0f,10.0f,-1700.0f};		//�|�W�V����
	Vector3 m_scale = { 0.8f,0.8f,0.8f };		//�X�P�[��
	Quaternion m_rot = Quaternion::Identity;		//�L�����N�^�[�̉�]
	PlayerStateIdle* m_stateIdle = nullptr;		//�ҋ@���
	PlayerStateMove* m_stateMove = nullptr;		//�ړ����
	PlayerStateAim* m_stateAim = nullptr;		//�G�C�����
	Weapon* m_PlayerWeapon = nullptr;		//�v���C���[�̕���
	GameCamera* m_camera = nullptr;		//�J����
	Vector3 m_forward = Vector3::AxisZ;		//�O����
	CharacterController characon;		//�L�����R��
	Vector3 footStepValue = Vector3::Zero;		//footStep�̈ړ���
	prefab::SpriteRender* m_sprite = nullptr;
};