#pragma once
#include "IPlayer.h"

class Player:public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Draw();

private:
	IPlayer* currentState = nullptr;		//現在のステート
};
