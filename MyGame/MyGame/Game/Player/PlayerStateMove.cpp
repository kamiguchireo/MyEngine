#include "stdafx.h"
#include "PlayerStateMove.h"
#include "Player.h"

PlayerStateMove::~PlayerStateMove()
{

}

void PlayerStateMove::Update()
{
	if (GetAsyncKeyState(VK_LSHIFT))
	{	
		//左SHIFTが押されているとき
		//スプリントアニメーションを再生
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Sprint);
	}
	else if (GetAsyncKeyState(VK_LCONTROL))
	{
		//左CONTROLが押されているとき
		//歩きアニメーションを再生
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Walk);
	}
	else
	{
		//それ以外では
		//走りアニメーションを再生
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Run);
	}
	//移動方向
	Vector3 movedir = Vector3::Zero;
	
	//カメラの前方向をゲット
	movedir = g_camera3D->GetForward();
	movedir.y = 0.0f;
	movedir.Normalize();

	//キー入力による移動方向の計算
	//まずはカメラの移動方向を計算
	Vector3 KeyDir = movedir * g_pad[0]->GetLStickYF();
	//カメラの右方向をゲット
	Vector3 playerRight = Cross(Vector3::Up, movedir);
	//カメラの左右の移動方向を計算
	KeyDir += playerRight* g_pad[0]->GetLStickXF();
	KeyDir.Normalize();

	//プレイヤーの前方向をセット
	m_Player->SetForward(KeyDir);
	//プレイヤーの右方向をセット
	m_Player->SetRight(playerRight);
}
