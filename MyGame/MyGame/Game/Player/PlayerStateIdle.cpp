#include "stdafx.h"
#include "PlayerStateIdle.h"
#include "Player.h"

PlayerStateIdle::~PlayerStateIdle()
{

}

void PlayerStateIdle::Update()
{
	//待機状態のアニメーションを再生
	m_Player->PlayAnimation(enPlayerAnimation_Rifle_Idle);
}
