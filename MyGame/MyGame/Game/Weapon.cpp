#include "stdafx.h"
#include "Weapon.h"

Weapon::~Weapon()
{
	//�������
	if (m_Model != nullptr)
	{
		DeleteGO(m_Model);
		m_Model = nullptr;
	}

}

void Weapon::Init(Skeleton* sk,bool IsDither)
{
	m_skeleton = sk;
	//���f����New
	m_Model = NewGO<prefab::ModelRender>(3);
	//�t�@�C���p�X���Z�b�g
	m_Model->SetTkmFilePath("Assets/modelData/AK_74M.tkm");
	//�f�B�U�����O��K�����邩�ǂ����̃t���O
	m_Model->SetDitherFlag(IsDither);
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
	//����̃|�W�V�������擾
	WeaponPos = m_skeleton->GetBone(m_skeleton->GetWeaponBoneNum())->GetPosition();
	//���킩��J�����̒����_�Ɍ������x�N�g��
	Vector3 WeaponToLeftHand = Vector3::Zero;
	WeaponToLeftHand = g_camera3D->GetTarget() - WeaponPos;
	//���K��
	WeaponToLeftHand.Normalize();
	g_graphicsEngine->GetDecale()->AddStartPos(m_skeleton->GetBone(m_skeleton->GetWeaponBoneNum())->GetPosition(), g_camera3D->GetRight(),WeaponToLeftHand);
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