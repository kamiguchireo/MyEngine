#include "stdafx.h"
#include "EnemyHitBox.h"

EnemyHitBox::EnemyHitBox()
{

}

EnemyHitBox::~EnemyHitBox()
{
	for (int i = 0; i < 9; i++)
	{
		if (m_colldetection[i] != nullptr)
		{
			delete m_colldetection[i];
			m_colldetection[i] = nullptr;
		}
	}
}

void EnemyHitBox::BuildCollisionDetection()
{
	for (int i = 0; i < 9; i++)
	{
		m_colldetection[i] = new PhysicsGhostObject;
	}
	m_ColOnSkeletonNum[0] = m_skeleton->FindBoneID(L"mixamorig:Head");
	m_ColOnSkeletonNum[1] = m_skeleton->FindBoneID(L"mixamorig:Hips");
	m_colldetection[0]->CreateBox(
		m_skeleton->GetBone(m_ColOnSkeletonNum[0])->GetPosition(),
		m_skeleton->GetBone(m_ColOnSkeletonNum[0])->GetRotation(),
		{ 17.0f,24.0f,20.0f }
	);
}

void EnemyHitBox::Init(Skeleton* sk)
{
	//スケルトンを代入
	m_skeleton = sk;
	//ヒットボックスを構築
	BuildCollisionDetection();
}

void EnemyHitBox::UpdateCollisionDetection()
{
	Quaternion q_rot = m_skeleton->GetBone(m_ColOnSkeletonNum[0])->GetRotation();
	Vector3 m_pos = { 0.0f,5.0f,3.0f };
	q_rot.Apply(m_pos);
	m_colldetection[0]->UpdateWorldMatrix(
		m_skeleton->GetBone(m_ColOnSkeletonNum[0])->GetPosition() + m_pos,
		q_rot
	);
}