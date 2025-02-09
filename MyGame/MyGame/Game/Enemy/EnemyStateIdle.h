#pragma once
#include "IEnemy.h"

class EnemyStateIdle:public IEnemy
{
public:
	EnemyStateIdle(Enemy* en) :IEnemy(en) {}
	~EnemyStateIdle();

	void Update();

private:
	const float stopTime = 5.0f;		//止まっている時間
	float m_time = 0.0f;		//現在の時間
};

