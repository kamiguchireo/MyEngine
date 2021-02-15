#include "stdafx.h"
#include "PlayerWeapon.h"
#include "Player.h"

PlayerWeapon::~PlayerWeapon()
{

}

void PlayerWeapon::Init()
{
	m_Model = NewGO<prefab::ModelRender>(2);
	m_Model->SetTkmFilePath("Assets/modelData/AK_74M.tkm");
}

void PlayerWeapon::Start()
{

}

void PlayerWeapon::Update()
{
	m_weaponMat = m_Player->GetWeaponBoneMat();

	m_Model->SetWorldMatrix(m_weaponMat);
	m_Model->SetUpdateFlag(false);
}