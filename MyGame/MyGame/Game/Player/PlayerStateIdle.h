#pragma once
#include "IPlayer.h"

class PlayerStateIdle:public IPlayer
{
public:
	PlayerStateIdle(Player* pl) :IPlayer(pl) {}
	~PlayerStateIdle();
	void Update();

private:
};