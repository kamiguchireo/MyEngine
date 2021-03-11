#include "stdafx.h"
#include "Weapon.h"

Weapon::~Weapon()
{
	if (m_Model != nullptr)
	{
		DeleteGO(m_Model);
		m_Model = nullptr;
	}

	if (m_Decale != nullptr)
	{
		DeleteGO(m_Decale);
		m_Decale = nullptr;
	}
}

void Weapon::Init(Skeleton* sk,bool DitherFlag)
{
	m_skeleton = sk;
	m_Model = NewGO<prefab::ModelRender>(3);
	m_Model->SetTkmFilePath("Assets/modelData/AK_74M.tkm");
	m_Model->SetDitherFlag(DitherFlag);
	m_Decale = NewGO<Decale>(4);

}
bool Weapon::Start()
{
	LeftHandBoneNo = m_skeleton->FindBoneID(L"mixamorig:LeftHand");

	return true;
}

void Weapon::AddDecale()
{
	//����̃|�W�V����
	Vector3 WeaponPos = Vector3::Zero;
	//����̃|�W�V����
	Vector3 LeftHandPos = Vector3::Zero;
	//����̃|�W�V�������擾
	WeaponPos = m_skeleton->GetBone(m_skeleton->GetWeaponBoneNum())->GetPosition();
	//����̃|�W�V�������擾
	LeftHandPos = m_skeleton->GetBone(LeftHandBoneNo)->GetPosition();
	//���킩�獶��Ɍ������x�N�g��
	Vector3 WeaponToLeftHand = Vector3::Zero;
	WeaponToLeftHand = g_camera3D->GetTarget() - WeaponPos;
	//���K��
	WeaponToLeftHand.Normalize();
	m_Decale->AddStartPos(m_skeleton->GetBone(m_skeleton->GetWeaponBoneNum())->GetPosition(), WeaponToLeftHand);
}

void Weapon::Update()
{
	//����p�̍s����{�[������擾
	m_weaponMat = m_skeleton->GetWeaponMatrix();
	//����Ƀ��[���h�s����Z�b�g
	m_Model->SetWorldMatrix(m_weaponMat);
	//���ڍs����Z�b�g���Ă���̂ōs��̌v�Z�͂��Ȃ�
	m_Model->SetUpdateFlag(false);
}