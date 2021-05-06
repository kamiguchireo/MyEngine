#pragma once
#include "SourceFile/Physics/PhysicsGhostObject.h"

class EnemyHitBox:public IGameObject
{
public:
	EnemyHitBox();
	~EnemyHitBox();

	//������
	void Init(Skeleton* sk);

	//�X�V�֐�
	void Update();
private:
	//�����蔻��̃T�C�Y��������
	void InitSize();

	//�����蔻����\�z
	void BuildCollisionDetection();

	//���Z����|�W�V������������
	void InitAddPos();

	//�����蔻����X�V
	void UpdateCollisionDetection();

private:
	Skeleton* m_skeleton = nullptr;
	PhysicsGhostObject* m_colldetection[HitBoxNum::Num] = { nullptr };
	int m_ColOnSkeletonNum[HitBoxNum::Num] = { -1 };
	Vector3 m_AddPos[HitBoxNum::Num] = { Vector3::Zero };
	Vector3 m_ColSize[HitBoxNum::Num] = { Vector3::One };
};