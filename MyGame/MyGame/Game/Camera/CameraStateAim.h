#pragma once
#include "IGameCamera.h"

class CameraStateAim:public IGameCamera
{
public:
	CameraStateAim();
	~CameraStateAim();

	void Update(Vector3& pivotpos,float& rot);
	void SetAddPosY(float* f)
	{
		AddPosY = f;
	}
private:
	float CameraDist = 200.0f;			//カメラからターゲットまでの距離
	//float rot = 0.0f;			//回転量
	float* AddPosY = nullptr;		//ポジションに加算する上方向の値
	const float MaxAddPos = 150.0f;		//ポジションに加算できる上方向の最大値
	const float MinAddPos = -150.0f;		//ポジションに加算できる上方向の最小値
	const float DefaultCameraHeight = 130.0f;		//カメラのデフォルトの高さ
	int DefaultPoint[2] = { 500,300 };
	float sensiX = 0.00025f;
	float sensiY = 0.1f;
};

