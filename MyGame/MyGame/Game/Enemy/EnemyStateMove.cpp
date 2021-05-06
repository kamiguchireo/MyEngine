#include "stdafx.h"
#include "EnemyStateMove.h"
#include "Enemy.h"

EnemyStateMove::~EnemyStateMove()
{

}

void EnemyStateMove::Update()
{
	m_Enemy->PlayAnimation(enEnemyAnimation_Rifle_Walk);
}