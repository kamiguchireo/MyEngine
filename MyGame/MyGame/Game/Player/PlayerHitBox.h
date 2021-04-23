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

	//������
	void Init(Skeleton* sk);

	//�����蔻����X�V
	void UpdateCollisionDetection();

private:
	//�����蔻��̃T�C�Y��������
	void InitSize();

	//�����蔻����\�z
	void BuildCollisionDetection();

	//���Z����|�W�V������������
	void InitAddPos();
private:
	Skeleton* m_skeleton = nullptr;
	PhysicsGhostObject* m_colldetection[HitBoxNum::Num] = { nullptr };
	int m_ColOnSkeletonNum[HitBoxNum::Num] = { -1 };
	Vector3 m_AddPos[HitBoxNum::Num] = { Vector3::Zero };
	Vector3 m_ColSize[HitBoxNum::Num] = { Vector3::One };
};
