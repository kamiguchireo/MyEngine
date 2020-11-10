#include "stdafx.h"
#include "PlayerStateMove.h"

PlayerStateMove::PlayerStateMove()
{

}

PlayerStateMove::~PlayerStateMove()
{

}

void PlayerStateMove::Update(Vector3& pos, Quaternion& /*rot*/, Vector3& /*scale*/)
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		pos.x++;
	}
}
