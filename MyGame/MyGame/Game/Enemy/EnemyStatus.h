#pragma once

class Enemy;
class EnemyStatus
{
public: 
	EnemyStatus(Enemy* en) :
		m_en(en)
	{

	}
	~EnemyStatus()
	{

	}

	//ダメージを受ける
	//i		ダメージ量
	void Damage(int i);

	//エネミーの死亡フラグを立てる
	void Dead();

private:
	int m_hp = 100;		//ヒットポイント
	Enemy* m_en = nullptr;		//エネミー
};