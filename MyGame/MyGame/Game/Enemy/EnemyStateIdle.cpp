#include "stdafx.h"
#include "EnemyStateIdle.h"
#include "Enemy.h"

EnemyStateIdle::~EnemyStateIdle()
{

}

void EnemyStateIdle::Update()
{
	//待機アニメーションを再生
	m_Enemy->PlayAnimation(enEnemyAnimation_Rifle_Idle);
	//現在の時間を加算
	m_time += g_gameTime.GetFrameDeltaTime();
	//現在の時間が止まっている時間より長くなった時
	if (m_time >= stopTime)
	{
		//ストップフラグをセットする
		m_Enemy->SetIsStop(false);
		m_time = 0.0f;
	}
}