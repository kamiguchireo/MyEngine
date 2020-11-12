#include "stdafx.h"
#include "PlayerStateMove.h"

PlayerStateMove::PlayerStateMove()
{

}

PlayerStateMove::~PlayerStateMove()
{

}

void PlayerStateMove::Update(Vector3& pos, Quaternion& /*rot*/)
{
	pos.x += g_pad[0]->GetLStickXF() * 2.0f;
	pos.z += g_pad[0]->GetLStickYF() * 2.0f;
}
