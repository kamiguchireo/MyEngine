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

	void SetTarget(const Vector3& pos)
	{
		m_target = pos;
	}

	void ChangeState(IGameCamera* state)
	{
		currentState = state;
	}

	void SetCameraDist(float f)
	{
		TPScameraState.SetCameraDist(f);
	}

	void SetCameraState(CameraState state)
	{
		m_StateNum = state;
	}
private:
	CameraState m_StateNum = CameraState::TPS;
	IGameCamera* currentState = nullptr;
	CameraStateTPS TPScameraState;
	CameraStateAim AIMcameraState;
	Vector3 m_pos = { 0.0f, 100.0f, -300.0f };		//カメラの視点
	Vector3 m_target = { 0.0f, 100.0f, 0.0f };		//カメラの注視点
	Vector3 m_up = Vector3::Up;			//カメラの上方向
	float rot = 0.0f;			//回転量
	float AddPosY = 50.0f;		//ポジションに加算する上方向の値

};