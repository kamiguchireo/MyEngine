#include "stdafx.h"
#include "PlayerWeapon.h"
#include "Player.h"

PlayerWeapon::~PlayerWeapon()
{

}

void PlayerWeapon::Init(Player*pl)
{
	m_Player = pl;
	m_Model = NewGO<prefab::ModelRender>(3);
	m_Model->SetTkmFilePath("Assets/modelData/AK_74M.tkm");
}

bool PlayerWeapon::Start()
{
	return true;
}

void PlayerWeapon::Update()
{
	m_weaponMat = m_Player->GetWeaponBoneMat();

	m_Model->SetWorldMatrix(m_weaponMat);
	m_Model->SetUpdateFlag(false);
}