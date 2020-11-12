#include "stdafx.h"
#include "CameraStateTPS.h"

CameraStateTPS::CameraStateTPS()
{

}

CameraStateTPS::~CameraStateTPS()
{

}

void CameraStateTPS::Update(Vector3& /*pos*/, Vector3& target)
{
	rot += g_pad[0]->GetRStickXF()*0.05f;
	target.y += 50.0f;
	Vector3 pos = target;
	Vector3 addPos = Vector3::Zero;
	addPos.x = sinf(rot) * CameraDist;
	addPos.y = 50.0f;
	addPos.z -= cosf(rot) * CameraDist;
	pos += addPos;
	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(target);
}