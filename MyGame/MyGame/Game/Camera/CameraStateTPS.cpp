#include "stdafx.h"
#include "CameraStateTPS.h"

CameraStateTPS::CameraStateTPS()
{
	ShowCursor(false);
}

CameraStateTPS::~CameraStateTPS()
{

}

void CameraStateTPS::Update(Vector3& /*pos*/, Vector3& target)
{
	POINT pt;
	GetCursorPos(&pt);
	int lstx = pt.x;
	int lsty = pt.y;

	//右スティックの入力量から回転する量を決める
	//rot -= g_pad[0]->GetRStickXF() * 0.05f;
	rot += (DefaultPoint[0] - lstx) * sensiX;
	//最低限の高さの確保
	target.y += 90.0f;
	//最終的なカメラのポジション
	Vector3 pos = target;
	//最終的なカメラのターゲットのポジション
	Vector3 targetPos = target;
	//カメラのポジションに足すY方向の値を右スティックの入力量から決める
	//AddPosY -= g_pad[0]->GetRStickYF()*2.0f;
	AddPosY -= (DefaultPoint[1] - lsty) * sensiY;

	AddPosY = min(max(MinAddPos, AddPosY), MaxAddPos);
	//カメラのポジションに足すベクトル
	Vector3 addPos = Vector3::Zero;
	//rotからカメラの位置を決める
	addPos.x = sinf(rot) * CameraDist;
	addPos.y = AddPosY;
	addPos.z -= cosf(rot) * CameraDist;
	pos += addPos;

	SetCursorPos(500, 300);
	//カメラにセット
	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(targetPos);
}