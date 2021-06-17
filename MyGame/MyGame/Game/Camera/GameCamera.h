#pragma once
#include "IGameCamera.h"
#include "CameraStateTPS.h"
#include "CameraStateAim.h"

enum class CameraState {
	TPS,
	AIM,
	NUM
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
		if (m_StateNum != state)
		{
			m_StateNum = state;
			switch (m_StateNum)
			{
			case CameraState::TPS:
				//TPSカメラにする
				ChangeState(&TPScameraState);
				currentState->SetAddPosY(50.0f);
				break;
			case CameraState::AIM:
				//AIMカメラにする
				ChangeState(&AIMcameraState);
				currentState->SetAddPosY(0.0f);
				break;
			default:
				break;
			}
		}
	}

	//計算の起点となる位置をセット
	void SetPivotPos(const Vector3& pos)
	{
		m_pivotPos = pos;
	}

	void SetHeadPos(const Vector3& pos)
	{
		m_HeadPos = pos;
	}
private:


private:
	CameraState m_StateNum = CameraState::NUM;
	IGameCamera* currentState = nullptr;
	CameraStateTPS TPScameraState;
	CameraStateAim AIMcameraState;
	Vector3 m_up = Vector3::Up;			//カメラの上方向
	float rot = 0.0f;			//回転量
	float AddPosY = 50.0f;		//ポジションに加算する上方向の値
	Vector3 m_pivotPos = { 0.0f,0.0f,0.0f };
	Vector3 m_HeadPos = Vector3::Zero;
};