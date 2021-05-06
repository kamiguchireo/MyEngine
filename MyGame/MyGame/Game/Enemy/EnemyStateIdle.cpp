#include "stdafx.h"
#include "EnemyStateIdle.h"
#include "Enemy.h"

EnemyStateIdle::~EnemyStateIdle()
{

}

void EnemyStateIdle::Update()
{
	m_Enemy->UpdateAnimation(enEnemyAnimation_Rifle_Idle);
}