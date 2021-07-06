#include "stdafx.h"
#include "EnemyHitBox.h"
#include "Enemy.h"

EnemyHitBox::EnemyHitBox()
{

}

EnemyHitBox::~EnemyHitBox()
{
	//解放処理
	for (int i = 0; i < HitBoxNum::Num; i++)
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
	//各コリジョンのサイズを初期化
	m_ColSize[HitBoxNum::Head] = { 17.0f,24.0f,20.0f };
	m_ColSize[HitBoxNum::Spine2] = { 30.0f,30.0f,27.0f };
	m_ColSize[HitBoxNum::Spine] = { 30.0f,20.0f,23.0f };
	m_ColSize[HitBoxNum::Hips] = { 30.0f,10.0f,23.0f };
	m_ColSize[HitBoxNum::LeftUpLeg] = { 15.0f,30.0f,19.0f };
	m_ColSize[HitBoxNum::RightUpLeg] = { 15.0f,30.0f,19.0f };
	m_ColSize[HitBoxNum::LeftLeg] = { 13.0f,35.0f,15.0f };
	m_ColSize[HitBoxNum::RightLeg] = { 13.0f,35.0f,15.0f };
	m_ColSize[HitBoxNum::LeftFoot] = { 10.0f,13.0f,10.0f };
	m_ColSize[HitBoxNum::RightFoot] = { 10.0f,13.0f,10.0f };
	m_ColSize[HitBoxNum::LeftToeBase] = { 10.0f,16.0f,10.0f };
	m_ColSize[HitBoxNum::RightToeBase] = { 10.0f,16.0f,10.0f };
	m_ColSize[HitBoxNum::LeftArm] = { 13.0f,25.0f,13.0f };
	m_ColSize[HitBoxNum::RightArm] = { 13.0f,25.0f,13.0f };
	m_ColSize[HitBoxNum::LeftForeArm] = { 10.0f,27.0f,10.0f };
	m_ColSize[HitBoxNum::RightForeArm] = { 10.0f,27.0f,10.0f };
	m_ColSize[HitBoxNum::LeftHand] = { 10.0f,12.0f,5.0f };
	m_ColSize[HitBoxNum::RightHand] = { 10.0f,12.0f,5.0f };

}

void EnemyHitBox::BuildCollisionDetection()
{
	for (int i = 0; i < HitBoxNum::Num; i++)
	{
		m_colldetection[i] = new PhysicsGhostObject;
	}
	//各コライダーに対応するボーンを検索
	m_ColOnSkeletonNum[HitBoxNum::Head] = m_skeleton->FindBoneID(L"mixamorig:Head");
	m_ColOnSkeletonNum[HitBoxNum::Spine2] = m_skeleton->FindBoneID(L"mixamorig:Spine2");
	m_ColOnSkeletonNum[HitBoxNum::Spine] = m_skeleton->FindBoneID(L"mixamorig:Spine");
	m_ColOnSkeletonNum[HitBoxNum::Hips] = m_skeleton->FindBoneID(L"mixamorig:Hips");
	m_ColOnSkeletonNum[HitBoxNum::LeftUpLeg] = m_skeleton->FindBoneID(L"mixamorig:LeftUpLeg");
	m_ColOnSkeletonNum[HitBoxNum::RightUpLeg] = m_skeleton->FindBoneID(L"mixamorig:RightUpLeg");
	m_ColOnSkeletonNum[HitBoxNum::LeftLeg] = m_skeleton->FindBoneID(L"mixamorig:LeftLeg");
	m_ColOnSkeletonNum[HitBoxNum::RightLeg] = m_skeleton->FindBoneID(L"mixamorig:RightLeg");
	m_ColOnSkeletonNum[HitBoxNum::LeftFoot] = m_skeleton->FindBoneID(L"mixamorig:LeftFoot");
	m_ColOnSkeletonNum[HitBoxNum::RightFoot] = m_skeleton->FindBoneID(L"mixamorig:RightFoot");
	m_ColOnSkeletonNum[HitBoxNum::LeftToeBase] = m_skeleton->FindBoneID(L"mixamorig:LeftToeBase");
	m_ColOnSkeletonNum[HitBoxNum::RightToeBase] = m_skeleton->FindBoneID(L"mixamorig:RightToeBase");
	m_ColOnSkeletonNum[HitBoxNum::LeftArm] = m_skeleton->FindBoneID(L"mixamorig:LeftArm");
	m_ColOnSkeletonNum[HitBoxNum::RightArm] = m_skeleton->FindBoneID(L"mixamorig:RightArm");
	m_ColOnSkeletonNum[HitBoxNum::LeftForeArm] = m_skeleton->FindBoneID(L"mixamorig:LeftForeArm");
	m_ColOnSkeletonNum[HitBoxNum::RightForeArm] = m_skeleton->FindBoneID(L"mixamorig:RightForeArm");
	m_ColOnSkeletonNum[HitBoxNum::LeftHand] = m_skeleton->FindBoneID(L"mixamorig:LeftHand");
	m_ColOnSkeletonNum[HitBoxNum::RightHand] = m_skeleton->FindBoneID(L"mixamorig:RightHand");

	for (int i = 0; i < HitBoxNum::Num; i++)
	{
		//ボックスコライダーを作成
		m_colldetection[i]->CreateBox(
			m_skeleton->GetBone(m_ColOnSkeletonNum[i])->GetPosition(),
			m_skeleton->GetBone(m_ColOnSkeletonNum[i])->GetRotation(),
			m_ColSize[i]
		);
		//各コリジョンのステートをデフォにセット
		m_colldetection[i]->SetActivationState(CollisionActivationState::Default);
	}
}

void EnemyHitBox::InitAddPos()
{
	//各コリジョンの位置を調整するためのベクトル
	m_AddPos[HitBoxNum::Head] = { 0.0f,5.0f,3.0f };
	m_AddPos[HitBoxNum::Spine2] = { 0.0f,0.0f,2.5f };
	m_AddPos[HitBoxNum::Spine ] = { 0.0f,0.0f,2.5f };
	m_AddPos[HitBoxNum::Hips] = { 0.0f,-5.0f,0.0f };
	m_AddPos[HitBoxNum::LeftUpLeg] = { 0.0f,16.0f,0.0f };
	m_AddPos[HitBoxNum::RightUpLeg] = { 0.0f,16.0f,0.0f };
	m_AddPos[HitBoxNum::LeftLeg] = { 0.0f,10.0f,0.0f };
	m_AddPos[HitBoxNum::RightLeg] = { 0.0f,10.0f,0.0f };	
	m_AddPos[HitBoxNum::LeftFoot] = { 0.0f,0.0f,-3.0f };
	m_AddPos[HitBoxNum::RightFoot] = { 0.0f,0.0f,-3.0f };
	m_AddPos[HitBoxNum::LeftToeBase] = { 0.0f,-1.0f,3.0f };
	m_AddPos[HitBoxNum::RightToeBase] = { 0.0f,-1.0f,3.0f };
	m_AddPos[HitBoxNum::LeftArm] = { 0.0f,6.0f,0.0f };
	m_AddPos[HitBoxNum::RightArm] = { 0.0f,6.0f,0.0f };
	m_AddPos[HitBoxNum::LeftForeArm] = { 0.0f,10.0f,0.0f };
	m_AddPos[HitBoxNum::RightForeArm] = { 0.0f,10.0f,0.0f };
	m_AddPos[HitBoxNum::LeftHand] = { 0.0f,6.0f,0.0f };
	m_AddPos[HitBoxNum::RightHand] = { 0.0f,6.0f,0.0f };

}

void EnemyHitBox::Init(Skeleton* sk,Enemy*en)
{
	//スケルトンを代入
	m_skeleton = sk;
	m_en = en;
	//ヒットボックスのサイズを初期化
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
		//回転を加算
		q_rot.Apply(m_pos);
		//コリジョンの位置を更新
		m_colldetection[i]->UpdateWorldMatrix(
			m_skeleton->GetBone(m_ColOnSkeletonNum[i])->GetPosition() + m_pos,
			q_rot
		);
	}
}

void EnemyHitBox::Update()
{
	for (int i = 0; i < HitBoxNum::Num; i++)
	{
		if (m_colldetection[i]->GetActivationState() == CollisionActivationState::Hit)
		{
			if (i == HitBoxNum::Head)
			{
				m_en->Damage(60);
			}
			else if (i >= HitBoxNum::Spine2 && i <= HitBoxNum::Hips)
			{
				m_en->Damage(20);
			}
			else if (i >= HitBoxNum::LeftUpLeg && i <= HitBoxNum::RightToeBase)
			{
				m_en->Damage(15);
			}
			else if (i >= HitBoxNum::LeftArm && i <= HitBoxNum::RightHand)
			{
				m_en->Damage(10);
			}

			//ステートをデフォにセット
			m_colldetection[i]->SetActivationState(CollisionActivationState::Default);
		}
	}
	//ボーンが1フレームずれるためコリジョンをアップデートする前にボーンを更新
	m_en->UpdateAnimation(0.0f);
	UpdateCollisionDetection();
}