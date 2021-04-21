#pragma once
#include "SourceFile/Physics/PhysicsGhostObject.h"

class EnemyHitBox:public IGameObject
{
public:
	EnemyHitBox();
	~EnemyHitBox();

	//‰Šú‰»
	void Init(Skeleton* sk);

	//“–‚½‚è”»’è‚ğXV
	void UpdateCollisionDetection();

private:
	//“–‚½‚è”»’è‚ğ\’z
	void BuildCollisionDetection();

private:
	Skeleton* m_skeleton = nullptr;
	PhysicsGhostObject* m_colldetection[10] = { nullptr };
	int m_ColOnSkeletonNum[10] = { -1 };
};