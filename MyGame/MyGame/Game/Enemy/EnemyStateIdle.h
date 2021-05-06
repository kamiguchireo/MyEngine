#pragma once
#include "IEnemy.h"

class EnemyStateIdle:public IEnemy
{
public:
	EnemyStateIdle(Enemy* en) :IEnemy(en) {}
	~EnemyStateIdle();

	void Update();

private:

};

