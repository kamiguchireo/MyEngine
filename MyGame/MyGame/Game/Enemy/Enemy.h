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
	//�A�j���[�V�������Đ�
	void PlayAnimation(int i)
	{
		m_animation.Play(i, 0.3f);
	}

	void SetIsStop(bool flag)
	{
		IsStop = flag;
	}

	//���S
	void Dead()
	{
		IsDead = true;
	}

	//�_���[�W���󂯂�
	void Damage(int i)
	{
		m_Status->Damage(i);
	}
	//�v���C���[�����邱�Ƃ��ł��邩
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