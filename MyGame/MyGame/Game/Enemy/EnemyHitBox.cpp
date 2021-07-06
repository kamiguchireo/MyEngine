#include "stdafx.h"
#include "EnemyHitBox.h"
#include "Enemy.h"

EnemyHitBox::EnemyHitBox()
{

}

EnemyHitBox::~EnemyHitBox()
{
	//�������
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
	//�e�R���W�����̃T�C�Y��������
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
	//�e�R���C�_�[�ɑΉ�����{�[��������
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
		//�{�b�N�X�R���C�_�[���쐬
		m_colldetection[i]->CreateBox(
			m_skeleton->GetBone(m_ColOnSkeletonNum[i])->GetPosition(),
			m_skeleton->GetBone(m_ColOnSkeletonNum[i])->GetRotation(),
			m_ColSize[i]
		);
		//�e�R���W�����̃X�e�[�g���f�t�H�ɃZ�b�g
		m_colldetection[i]->SetActivationState(CollisionActivationState::Default);
	}
}

void EnemyHitBox::InitAddPos()
{
	//�e�R���W�����̈ʒu�𒲐����邽�߂̃x�N�g��
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
	//�X�P���g������
	m_skeleton = sk;
	m_en = en;
	//�q�b�g�{�b�N�X�̃T�C�Y��������
	InitSize();
	//�q�b�g�{�b�N�X���\�z
	BuildCollisionDetection();
	//�X�V���ɉ��Z����|�W�V������������
	InitAddPos();
}

void EnemyHitBox::UpdateCollisionDetection()
{
	for (int i = 0; i < HitBoxNum::Num; i++)
	{
		Quaternion q_rot = m_skeleton->GetBone(m_ColOnSkeletonNum[i])->GetRotation();
		Vector3 m_pos = m_AddPos[i];
		//��]�����Z
		q_rot.Apply(m_pos);
		//�R���W�����̈ʒu���X�V
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

			//�X�e�[�g���f�t�H�ɃZ�b�g
			m_colldetection[i]->SetActivationState(CollisionActivationState::Default);
		}
	}
	//�{�[����1�t���[������邽�߃R���W�������A�b�v�f�[�g����O�Ƀ{�[�����X�V
	m_en->UpdateAnimation(0.0f);
	UpdateCollisionDetection();
}