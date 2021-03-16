#include "stdafx.h"
#include "PlayerStateAim.h"
#include "Player.h"

PlayerStateAim::~PlayerStateAim()
{

}

void PlayerStateAim::Update()
{
	//マウスの右ボタンが押された"
	if (GetKeyState(VK_LBUTTON) & (0x80))
	{
		//アニメーションを再生
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_fire);
		//m_Player->AddDecale();
	}
	else
	{
		//アニメーションを再生
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Down_To_Aim);
	}
}