#pragma once
#include "SourceFile/Physics/PhysicsGhostObject.h"

class EnemyHitBox:public IGameObject
{
public:
	EnemyHitBox();
	~EnemyHitBox();

	//初期化
	void Init(Skeleton* sk);

	//当たり判定を更新
	void UpdateCollisionDetection();

private:
	//当たり判定を構築
	void BuildCollisionDetection();

private:
	Skeleton* m_skeleton = nullptr;
	PhysicsGhostObject* m_colldetection[10] = { nullptr };
	int m_ColOnSkeletonNum[10] = { -1 };
};