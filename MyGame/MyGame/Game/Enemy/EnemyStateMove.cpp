#include "stdafx.h"
#include "EnemyStateMove.h"
#include "Enemy.h"

EnemyStateMove::~EnemyStateMove()
{

}

void EnemyStateMove::Update()
{
	m_Enemy->UpdateAnimation(enEnemyAnimation_Rifle_Walk);
}