#include "stdafx.h"
#include "EnemyStateAim.h"
#include "Enemy.h"

EnemyStateAim::~EnemyStateAim()
{

}

void EnemyStateAim::Update()
{
	m_Enemy->PlayAnimation(enPlayerAnimation_Rifle_Down_To_Aim);
}