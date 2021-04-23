#pragma once
#include "SourceFile/Physics/PhysicsGhostObject.h"

enum HitBoxNum {
	Head,
	Spine2,
	Spine,
	Hips,
	LeftUpLeg,
	RightUpLeg,
	LeftLeg,
	RightLeg,
	LeftFoot,
	RightFoot,
	LeftToeBase,
	RightToeBase,
	LeftArm,
	RightArm,
	LeftForeArm,
	RightForeArm,
	LeftHand,
	RightHand,
	Num
};
class PlayerHitBox :public IGameObject
{
public:
	PlayerHitBox();
	~PlayerHitBox();

	//初期化
	void Init(Skeleton* sk);

	//当たり判定を更新
	void UpdateCollisionDetection();

private:
	//当たり判定のサイズを初期化
	void InitSize();

	//当たり判定を構築
	void BuildCollisionDetection();

	//加算するポジションを初期化
	void InitAddPos();
private:
	Skeleton* m_skeleton = nullptr;
	PhysicsGhostObject* m_colldetection[HitBoxNum::Num] = { nullptr };
	int m_ColOnSkeletonNum[HitBoxNum::Num] = { -1 };
	Vector3 m_AddPos[HitBoxNum::Num] = { Vector3::Zero };
	Vector3 m_ColSize[HitBoxNum::Num] = { Vector3::One };
};
