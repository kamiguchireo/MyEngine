#pragma once
#include "IPlayer.h"
#include "Player.h"

class PlayerStateIdle:public IPlayer
{
public:
	PlayerStateIdle();
	~PlayerStateIdle();
	void Update();

private:
	Player* m_Instance = nullptr;
};