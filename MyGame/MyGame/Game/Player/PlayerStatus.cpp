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
	//���S�t���O�𗧂Ă�
	m_pl->Dead();
}