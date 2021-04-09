#pragma once
#include "IGameCamera.h"
#include "CameraStateTPS.h"
#include "CameraStateAim.h"

enum class CameraState {
	TPS,
	AIM,
};
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void Update();

	void ChangeState(IGameCamera* state)
	{
		currentState = state;
	}

	//カメラの距離を設定
	void SetCameraDist(float f)
	{
		TPScameraState.SetCameraDist(f);
	}

	//カメラのステートを設定
	void SetCameraState(CameraState state)
	{
		m_StateNum = state;
	}

	//計算の起点となる位置をセット
	void SetPivotPos(const Vector3& pos)
	{
		m_pivotPos = pos;
	}

private:
	CameraState m_StateNum = CameraState::TPS;
	IGameCamera* currentState = nullptr;
	CameraStateTPS TPScameraState;
	CameraStateAim AIMcameraState;
	Vector3 m_up = Vector3::Up;			//カメラの上方向
	float rot = 0.0f;			//回転量
	float AddPosY = 50.0f;		//ポジションに加算する上方向の値
	Vector3 m_pivotPos = { 0.0f,0.0f,0.0f };
};