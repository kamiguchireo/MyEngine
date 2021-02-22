#include "stdafx.h"
#include "Weapon.h"
#include "Player.h"

Weapon::~Weapon()
{

}

void Weapon::Init(Skeleton* sk)
{
	m_skeleton = sk;
	m_Model = NewGO<prefab::ModelRender>(3);
	m_Model->SetTkmFilePath("Assets/modelData/AK_74M.tkm");

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