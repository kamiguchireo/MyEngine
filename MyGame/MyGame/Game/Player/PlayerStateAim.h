#pragma once
#include "IPlayer.h"

class PlayerStateAim:public IPlayer
{
public:
	PlayerStateAim(Player* pl) :IPlayer(pl) {}
	~PlayerStateAim();
	void Update();
	
private:
	//‰ñ“]‚ÌXV
	void UpdateRotation();
};

