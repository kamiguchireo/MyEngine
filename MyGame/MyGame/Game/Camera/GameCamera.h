#pragma once
#include "IGameCamera.h"
#include "CameraStateTPS.h"

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
private:
	IGameCamera* currentState = nullptr;
	CameraStateTPS TPScameraState;
	Vector3 m_pos = { 0.0f, 100.0f, -300.0f };		//カメラの視点
	Vector3 m_target = { 0.0f, 100.0f, 0.0f };		//カメラの注視点
	Vector3 m_up = Vector3::Up;			//カメラの上方向
};