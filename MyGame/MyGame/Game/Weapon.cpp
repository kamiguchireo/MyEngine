#include "stdafx.h"
#include "Weapon.h"

Weapon::~Weapon()
{
	//解放処理
	if (m_Model != nullptr)
	{
		DeleteGO(m_Model);
		m_Model = nullptr;
	}

}

void Weapon::Init(Skeleton* sk,bool IsDither)
{
	m_skeleton = sk;
	//モデルをNew
	m_Model = NewGO<prefab::ModelRender>(3);
	//ファイルパスをセット
	m_Model->SetTkmFilePath("Assets/modelData/AK_74M.tkm");
	//ディザリングを適応するかどうかのフラグ
	m_Model->SetDitherFlag(IsDither);
}
bool Weapon::Start()
{
	LeftHandBoneNo = m_skeleton->FindBoneID(L"mixamorig:LeftHand");

	return true;
}

//void Weapon::AddDecale()
//{
//	//武器のポジション
//	Vector3 WeaponPos = Vector3::Zero;
//	//左手のポジション
//	Vector3 LeftHandPos = Vector3::Zero;
//	//武器のポジションを取得
//	WeaponPos = m_skeleton->GetBone(m_skeleton->GetWeaponBoneNum())->GetPosition();
//	//左手のポジションを取得
//	LeftHandPos = m_skeleton->GetBone(LeftHandBoneNo)->GetPosition();
//	//武器から左手に向けたベクトル
//	Vector3 WeaponToLeftHand = Vector3::Zero;
//	WeaponToLeftHand = g_camera3D->GetTarget() - WeaponPos;
//	//正規化
//	WeaponToLeftHand.Normalize();
//	g_graphicsEngine->GetDecale()->AddStartPos(m_skeleton->GetBone(m_skeleton->GetWeaponBoneNum())->GetPosition(), WeaponToLeftHand);
//}

void Weapon::Update()
{
	//武器用の行列をボーンから取得
	m_weaponMat = m_skeleton->GetWeaponMatrix();
	//武器にワールド行列をセット
	m_Model->SetWorldMatrix(m_weaponMat);
	//直接行列をセットしているので行列の計算はしない
	m_Model->SetUpdateFlag(false);
}