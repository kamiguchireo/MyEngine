#include "stdafx.h"
#include "Weapon.h"

Weapon::~Weapon()
{

}

void Weapon::Init(Skeleton* sk,bool DitherFlag)
{
	m_skeleton = sk;
	m_Model = NewGO<prefab::ModelRender>(3);
	m_Model->SetTkmFilePath("Assets/modelData/AK_74M.tkm");
	m_Model->SetDitherFlag(DitherFlag);
}
bool Weapon::Start()
{
	return true;
}

void Weapon::Update()
{
	m_weaponMat = m_skeleton->GetWeaponMatrix();
	m_Model->SetWorldMatrix(m_weaponMat);
	m_Model->SetUpdateFlag(false);
}