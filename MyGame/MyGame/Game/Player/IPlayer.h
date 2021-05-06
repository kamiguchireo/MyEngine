#pragma once

class Player;
//プレイヤーの基底クラス
class IPlayer
{
public:
	IPlayer(Player* pl) :
		m_Player(pl) {}
	virtual ~IPlayer()
	{
	}
	//更新関数
	virtual void Update() = 0;

protected:
	Player* m_Player;
};

