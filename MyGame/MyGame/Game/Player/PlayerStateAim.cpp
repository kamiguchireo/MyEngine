#include "stdafx.h"
#include "PlayerStateAim.h"
#include "Player.h"

PlayerStateAim::~PlayerStateAim()
{

}

void PlayerStateAim::WaistBend()
{
	//カメラの前方向を取得
	Vector3 aimForward = g_camera3D->GetForward();
	//先に正規化することでy成分が1の時真上を向いているようになる
	aimForward.Normalize();
	//角度を求める
	float RotY = aimForward.y * -45.0f;
	//X軸周りの回転行列
	Quaternion qRot = Quaternion::Identity;
	qRot.SetRotationDegX(RotY);
	//qRot.SetRotationDegX(atan2f(aimForward.z, aimForward.y));
	Matrix mRot = Matrix::Identity;
	mRot.MakeRotationFromQuaternion(qRot);
	//mRot.MakeRotationAxis(Vector3::AxisX, RotY);
	//プレイヤーの腰を回転
	m_plSkeleton->GetBone(m_SpineBoneNum)->SetUserMat(mRot);
	//m_plSkeleton->GetBone(m_RightArmBoneNum)->SetUserMat(mRot);
}

void PlayerStateAim::UpdateRotation()
{
	//カメラの前方向を取得
	Vector3 aimForward = g_camera3D->GetForward();
	//y成分は必要ないので0にする
	aimForward.y = 0.0f;
	//正規化
	aimForward.Normalize();
	//プレイヤーの前方向をセット
	m_Player->SetForward(aimForward);
	//腰から上も回転
	WaistBend();
}

void PlayerStateAim::Init()
{
	m_plSkeleton = m_Player->GetSkeleton();
	m_SpineBoneNum = m_plSkeleton->FindBoneID(L"mixamorig:Spine");
}



void PlayerStateAim::Update()
{	
	//回転の更新
	UpdateRotation();

	//マウスの左ボタンが押された"
	if (GetKeyState(VK_LBUTTON) & (0x80))
	{
		m_Player->Shooting();
		if (m_Player->IsWeaponAvailable())
		{
			//アニメーションを再生
			m_Player->PlayAnimation(enPlayerAnimation_Rifle_fire);
		}
		else
		{
			//アニメーションを再生
			m_Player->PlayAnimation(enPlayerAnimation_Rifle_Down_To_Aim);
		}
	}
	else
	{
		m_Player->WeaponRelease();
		//アニメーションを再生
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Down_To_Aim);
	}
}