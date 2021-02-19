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
		m_Player->PlayAnimation(5);
	}
	else
	{
		m_Player->PlayAnimation(4);
	}
}