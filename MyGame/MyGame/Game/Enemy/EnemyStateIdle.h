#pragma once
#include "IEnemy.h"

class EnemyStateIdle:public IEnemy
{
public:
	EnemyStateIdle(Enemy* en) :IEnemy(en) {}
	~EnemyStateIdle();

	void Update();

private:
	const float stopTime = 5.0f;		//�~�܂��Ă��鎞��
	float m_time = 0.0f;		//���݂̎���
};

