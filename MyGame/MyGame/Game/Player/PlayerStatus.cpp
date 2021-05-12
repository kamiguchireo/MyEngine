#include "stdafx.h"
#include "PlayerStatus.h"
#include "Player.h"

void PlayerStatus::Damage(int i)
{
	m_hp -= i;
	if (m_hp <= 0)
	{
		Dead();
	}
}

void PlayerStatus::Dead()
{
	//死亡フラグを立てる
	m_pl->Dead();
}