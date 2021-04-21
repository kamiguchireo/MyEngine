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
void EnemyHitBox::InitSize()
{
	m_ColSize[HitBoxNum::Head] = { 17.0f,24.0f,20.0f };
	m_ColSize[HitBoxNum::Spine2] = { 30.0f,30.0f,27.0f };
	m_ColSize[HitBoxNum::Spine] = { 30.0f,20.0f,23.0f };
	m_ColSize[HitBoxNum::Hips] = { 30.0f,10.0f,23.0f };
	m_ColSize[HitBoxNum::RightUpLeg] = { 15.0f,30.0f,20.0f };

}

void EnemyHitBox::BuildCollisionDetection()
{
	for (int i = 0; i < HitBoxNum::Num; i++)
	{
		m_colldetection[i] = new PhysicsGhostObject;
	}
	m_ColOnSkeletonNum[HitBoxNum::Head] = m_skeleton->FindBoneID(L"mixamorig:Head");
	m_ColOnSkeletonNum[HitBoxNum::Spine2] = m_skeleton->FindBoneID(L"mixamorig:Spine2");
	m_ColOnSkeletonNum[HitBoxNum::Spine] = m_skeleton->FindBoneID(L"mixamorig:Spine");
	m_ColOnSkeletonNum[HitBoxNum::Hips] = m_skeleton->FindBoneID(L"mixamorig:Hips");
	m_ColOnSkeletonNum[HitBoxNum::RightUpLeg] = m_skeleton->FindBoneID(L"mixamorig:RightUpLeg");

	for (int i = 0; i < HitBoxNum::Num; i++)
	{
		m_colldetection[i]->CreateBox(
			m_skeleton->GetBone(m_ColOnSkeletonNum[i])->GetPosition(),
			m_skeleton->GetBone(m_ColOnSkeletonNum[i])->GetRotation(),
			m_ColSize[i]
		);
	}
}

void EnemyHitBox::InitAddPos()
{
	m_AddPos[HitBoxNum::Head] = { 0.0f,5.0f,3.0f };
	m_AddPos[HitBoxNum::Spine2] = { 0.0f,0.0f,2.5f };
	m_AddPos[HitBoxNum::Spine ] = { 0.0f,0.0f,2.5f };
	m_AddPos[HitBoxNum::Hips] = { 0.0f,-5.0f,0.0f };
	m_AddPos[HitBoxNum::RightUpLeg] = { 0.0f,15.0f,0.0f };

}

void EnemyHitBox::Init(Skeleton* sk)
{
	//スケルトンを代入
	m_skeleton = sk;
	//火っとボックスのサイズを初期化
	InitSize();
	//ヒットボックスを構築
	BuildCollisionDetection();
	//更新時に加算するポジションを初期化
	InitAddPos();
}

void EnemyHitBox::UpdateCollisionDetection()
{
	for (int i = 0; i < HitBoxNum::Num; i++)
	{
		Quaternion q_rot = m_skeleton->GetBone(m_ColOnSkeletonNum[i])->GetRotation();
		Vector3 m_pos = m_AddPos[i];
		q_rot.Apply(m_pos);
		m_colldetection[i]->UpdateWorldMatrix(
			m_skeleton->GetBone(m_ColOnSkeletonNum[i])->GetPosition() + m_pos,
			q_rot
		);
	}
}