#pragma once
#include "IEnemy.h"

class EnemyStateAim:public IEnemy
{
public:
	EnemyStateAim(Enemy*en):IEnemy(en)
	{
	}

	~EnemyStateAim();
	
	void Update();

private:

};

