#pragma once
#include "IPlayer.h"

class PlayerStateIdle:public IPlayer
{
public:
	PlayerStateIdle();
	~PlayerStateIdle();
	void Update(Vector3& /*pos*/, Quaternion& /*rot*/);

private:
};