#pragma once
#include "IPlayer.h"

class PlayerStateMove:public IPlayer
{
public:
	PlayerStateMove(Player* pl) :IPlayer(pl) {}
	~PlayerStateMove();

	void Update();
private:
	Vector3 m_forward = Vector3::Zero;
};

