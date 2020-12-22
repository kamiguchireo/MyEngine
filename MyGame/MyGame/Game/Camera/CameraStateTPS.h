#pragma once
#include "IGameCamera.h"

class CameraStateTPS :public IGameCamera
{
public:
	CameraStateTPS();
	~CameraStateTPS();

	void Update(Vector3& pos, Vector3& target);

private:
	float CameraDist = 200.0f;			//カメラからターゲットまでの距離
	float rot = 0.0f;			//回転量
	float AddTargetPosY = 35.0f;		//ターゲットに加算する上方向の値
};

