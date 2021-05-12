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
#include "EnemyStatus.h"

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
	//�A�j���[�V�������Đ�
	void PlayAnimation(int i)
	{
		m_animation.Play(i, 0.3f);
	}

	void SetIsStop(bool flag)
	{
		IsStop = flag;
	}

	void Dead()
	{
		IsDead = true;
	}

private:
	//���̃p�X�֕ύX
	void ChangeNextPass();
	//�X�e�[�g�̕ύX
	//state		�X�e�[�g
	void ChangeState(IEnemy* state)
	{
		currentState = state;
	}
private:
	IEnemy* currentState = nullptr;		//���݂̃X�e�[�g
	prefab::ModelRender* m_enemyModel = nullptr;		//�G�l�~�[�̃��f��
	Skeleton m_skeleton;
	Engine::Animation m_animation;		//�A�j���[�V����
	Engine::AnimationClip m_animClip[enEnemyAnimation_Num];		//�A�j���[�V�����N���b�v
	Vector3 m_pos = { 0.0f,10.0f,-100.0f };		//�|�W�V����
	Vector3 m_scale = Vector3::One;		//�g�嗦
	Quaternion m_rot = Quaternion::Identity;		//��]��
	CharacterController* characon = nullptr;
	float rot = 0.0f;
	Path* m_path = nullptr;		//�p�X
	std::vector<Vector3> m_PassPos;
	int m_PassSize = 0;		//�p�X�����Ă���z��̃T�C�Y
	int CurrentPass = 0;		//���݂̃p�X
	int NextPass = 0;		//���̃p�X
	Weapon* m_weapon = nullptr;
	EnemyHitBox* m_HitBox = nullptr;
	EnemyStateIdle* m_stateIdle = nullptr;		//�ҋ@���
	EnemyStateMove* m_stateMove = nullptr;		//�ړ����
	EnemyStateAim* m_stateAim = nullptr;		//�G�C�����
	bool IsStop = false;		//�~�܂��Ă��邩�ǂ���
	Vector3 m_gravity = Vector3::Zero;		//�d�͂ɂ�����
	const float PassDist = 10.0f;		//�p�X�͈̔�
	std::unique_ptr<EnemyStatus> m_Status = nullptr;
	bool IsDead = false;		//����ł��邩�ǂ���
};