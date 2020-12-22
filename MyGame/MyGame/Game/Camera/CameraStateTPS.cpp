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
	//右スティックの入力量から回転する量を決める
	rot -= g_pad[0]->GetRStickXF() * 0.05f;
	//最低限の高さの確保
	target.y += 50.0f;
	//最終的なカメラのポジション
	Vector3 pos = target;
	//最終的なカメラのターゲットのポジション
	Vector3 targetPos = target;
	//カメラのターゲットに足すY方向の値を右スティックの入力量から決める
	AddTargetPosY += g_pad[0]->GetRStickYF()*2.0f;
	AddTargetPosY = min(max(-50.0f, AddTargetPosY), 200.0f);
	//カメラのターゲットのポジションに足す
	targetPos.y += AddTargetPosY;
	//カメラのポジションに足すベクトル
	Vector3 addPos = Vector3::Zero;
	//rotからカメラの位置を決める
	addPos.x = sinf(rot) * CameraDist;
	addPos.y = 80.0f;
	addPos.z -= cosf(rot) * CameraDist;
	pos += addPos;

	//カメラにセット
	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(targetPos);
}