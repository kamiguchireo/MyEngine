#pragma once
#include "IPlayer.h"

class PlayerStateMove:public IPlayer
{
public:
	PlayerStateMove(Player* pl) :IPlayer(pl) {}
	~PlayerStateMove();

	void Update();
private:
};

