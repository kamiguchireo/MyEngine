#pragma once
#include "IEnemy.h"

class EnemyStateMove:public IEnemy
{
public:
	EnemyStateMove(Enemy* en) :IEnemy(en) {}
	~EnemyStateMove();

	void Update();
private:

};

