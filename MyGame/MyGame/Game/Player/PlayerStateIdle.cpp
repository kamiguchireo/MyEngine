#include "stdafx.h"
#include "PlayerStateIdle.h"
#include "Player.h"

PlayerStateIdle::~PlayerStateIdle()
{

}

void PlayerStateIdle::Update()
{
	//�ҋ@��Ԃ̃A�j���[�V�������Đ�
	m_Player->PlayAnimation(enPlayerAnimation_Rifle_Idle);
}
