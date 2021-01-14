#include "stdafx.h"
#include "PlayerWeapon.h"
#include "Player.h"

PlayerWeapon::~PlayerWeapon()
{

}

void PlayerWeapon::Start()
{
	m_Model = NewGO<prefab::ModelRender>(0);
	m_Model->SetTkmFilePath("Assets/modelData/AK_74M.tkm");
	m_Model->SetVSEntryPoint("VSMain");
	m_Model->SetScale({ 0.8f,0.8f,0.8f });
}
void PlayerWeapon::Update()
{
	m_weaponPos = m_Player->GetWeaponBonePos();
	m_weaponRot = m_Player->GetWeaponBoneRot();
	m_weaponMat = m_Player->GetWeaponBoneMat();
	m_Model->SetWorldMatrix(m_weaponMat);
	m_Model->SetUpdateFlag(false);
	//m_Model->SetPosition({ 0.0f, 100.0f, 0.0f });
}