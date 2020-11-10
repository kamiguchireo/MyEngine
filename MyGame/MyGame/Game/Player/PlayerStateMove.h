#pragma once
#include "IPlayer.h"

class PlayerStateMove:public IPlayer
{
public:
	PlayerStateMove();
	~PlayerStateMove();

	void Update(Vector3& pos, Quaternion& /*rot*/, Vector3& /*scale*/);
private:
};

