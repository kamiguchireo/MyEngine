#include "stdafx.h"
#include "EnemyStatus.h"
#include "Enemy.h"

void EnemyStatus::Damage(int i)
{
	m_hp -= i;
	if (m_hp <= 0)
	{
		Dead();
	}
}

void EnemyStatus::Dead()
{
	//Ž€–Sƒtƒ‰ƒO‚ð—§‚Ä‚é
	m_en->Dead();
}