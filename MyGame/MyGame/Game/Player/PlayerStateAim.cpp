#include "stdafx.h"
#include "PlayerStateAim.h"
#include "Player.h"

PlayerStateAim::~PlayerStateAim()
{

}

void PlayerStateAim::UpdateRotation()
{
	//カメラの前方向を取得
	Vector3 aimForward = g_camera3D->GetForward();
	//y成分は必要ないので0にする
	aimForward.y = 0.0f;
	//正規化
	aimForward.Normalize();
	//二つのベクトルに直行するベクトルを取得
	Vector3 Axis = Cross(Vector3::Front, aimForward);
	//正規化
	Axis.Normalize();
	//ベクトルの大きさ1なので二つのベクトルのcosθのみが残る
	float dot = Dot(Vector3::Front, aimForward);
	Quaternion rot = Quaternion::Identity;
	//プレイヤーを視点方向に回転
	rot.SetRotation(Axis, acosf(dot));
	//プレイヤーに適応
	m_Player->SetRot(rot);
}

void PlayerStateAim::Update()
{	
	//回転の更新
	UpdateRotation();

	//マウスの左ボタンが押された"
	if (GetKeyState(VK_LBUTTON) & (0x80))
	{
		//アニメーションを再生
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_fire);
		m_Player->AddDecale();
	}
	else
	{
		//アニメーションを再生
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Down_To_Aim);
	}
}