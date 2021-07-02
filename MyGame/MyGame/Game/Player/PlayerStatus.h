#pragma once

class Player;
class PlayerStatus
{
public:
	PlayerStatus(Player* pn) :
		m_pl(pn)
	{

	}
	~PlayerStatus()
	{

	}

	//ダメージを受ける
	void Damage(int i);

	//プレイヤーの死亡フラグを立てる
	void Dead();

private:
	Player* m_pl = nullptr;		//プレイヤー
	int m_hp = 100;		//ヒットポイント
};

