#pragma once
#include "IPlayer.h"

class PlayerStateAim:public IPlayer
{
public:
	PlayerStateAim(Player* pl) :IPlayer(pl) {}
	~PlayerStateAim();
	void Update();
};

