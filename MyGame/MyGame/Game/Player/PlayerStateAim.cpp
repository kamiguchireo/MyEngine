#include "stdafx.h"
#include "PlayerStateAim.h"
#include "Player.h"

PlayerStateAim::~PlayerStateAim()
{

}

void PlayerStateAim::Update()
{
	//�}�E�X�̉E�{�^���������ꂽ"
	if (GetKeyState(VK_LBUTTON) & (0x80))
	{
		m_Player->PlayAnimation(5);
	}
	else
	{
		m_Player->PlayAnimation(4);
	}
}