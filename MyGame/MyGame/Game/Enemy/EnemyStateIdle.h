#pragma once
#include "IEnemy.h"

class EnemyStateIdle:public IEnemy
{
public:
	EnemyStateIdle(Enemy* en) :IEnemy(en) {}
	~EnemyStateIdle();

	void Update();

private:
	const float stopTime = 5.0f;		//~‚Ü‚Á‚Ä‚¢‚éŠÔ
	float m_time = 0.0f;		//Œ»İ‚ÌŠÔ
};

