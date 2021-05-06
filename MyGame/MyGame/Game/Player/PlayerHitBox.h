#pragma once
#include "SourceFile/Physics/PhysicsGhostObject.h"

class Player;
class PlayerHitBox :public IGameObject
{
public:
	PlayerHitBox();
	~PlayerHitBox();

	//初期化
	void Init(Skeleton* sk, Player* pl);

	//更新関数
	void Update();

private:
	//当たり判定のサイズを初期化
	void InitSize();

	//当たり判定を構築
	void BuildCollisionDetection();

	//加算するポジションを初期化
	void InitAddPos();

	//当たり判定を更新
	void UpdateCollisionDetection();

private:
	Skeleton* m_skeleton = nullptr;
	Player* m_pl = nullptr;
	PhysicsGhostObject* m_colldetection[HitBoxNum::Num] = { nullptr };
	int m_ColOnSkeletonNum[HitBoxNum::Num] = { -1 };
	Vector3 m_AddPos[HitBoxNum::Num] = { Vector3::Zero };
	Vector3 m_ColSize[HitBoxNum::Num] = { Vector3::One };
};
