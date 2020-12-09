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
	Vector3 CameraFront = g_camera3D->GetForward();
	Vector3 CameraRight = g_camera3D->GetRight();
	CameraFront.y = 0.0f;
	CameraRight.y = 0.0f;
	CameraFront.Normalize();
	CameraRight.Normalize();

	pos.x += g_pad[0]->GetLStickXF() * 2.0f * CameraRight.x + g_pad[0]->GetLStickYF() * 2.0f * CameraFront.x;
	pos.z += g_pad[0]->GetLStickXF() * 2.0f * CameraRight.z + g_pad[0]->GetLStickYF() * 2.0f * CameraFront.z;
}
