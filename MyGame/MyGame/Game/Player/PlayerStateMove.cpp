#include "stdafx.h"
#include "PlayerStateMove.h"
#include "Player.h"

PlayerStateMove::~PlayerStateMove()
{

}

void PlayerStateMove::Update()
{
	Vector3 pos = Vector3::Zero;
	Vector3 CameraFront = g_camera3D->GetForward();
	Vector3 CameraRight = g_camera3D->GetRight();
	CameraFront.y = 0.0f;
	CameraRight.y = 0.0f;
	CameraFront.Normalize();
	CameraRight.Normalize();

	pos.x += g_pad[0]->GetLStickXF() * 2.0f * CameraRight.x + g_pad[0]->GetLStickYF() * 2.0f * CameraFront.x;
	pos.z += g_pad[0]->GetLStickXF() * 2.0f * CameraRight.z + g_pad[0]->GetLStickYF() * 2.0f * CameraFront.z;
	m_Player->AddPosition(pos);
}
