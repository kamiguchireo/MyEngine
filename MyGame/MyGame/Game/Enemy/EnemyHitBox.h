#pragma once
#include "SourceFile/Physics/PhysicsGhostObject.h"

class EnemyHitBox:public IGameObject
{
public:
	EnemyHitBox();
	~EnemyHitBox();

	//������
	void Init(Skeleton* sk);

	//�����蔻����X�V
	void UpdateCollisionDetection();

private:
	//�����蔻����\�z
	void BuildCollisionDetection();

private:
	Skeleton* m_skeleton = nullptr;
	PhysicsGhostObject* m_colldetection[10] = { nullptr };
	int m_ColOnSkeletonNum[10] = { -1 };
};