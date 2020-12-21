#include "stdafx.h"
#include "PlayerStateIdle.h"
#include "Player.h"

PlayerStateIdle::~PlayerStateIdle()
{

}

void PlayerStateIdle::Update()
{
	m_Player->PlayAnimation(0);
}
