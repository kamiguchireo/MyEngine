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
		//�A�j���[�V�������Đ�
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_fire);
		//m_Player->AddDecale();
	}
	else
	{
		//�A�j���[�V�������Đ�
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Down_To_Aim);
	}
}