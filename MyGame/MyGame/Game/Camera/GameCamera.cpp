#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	//TPSカメラにする
	SetCameraState(CameraState::TPS);
}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//g_camera3D->SetUp(m_up);
	return true;
}

void GameCamera::Update()
{
	currentState->Update(m_pivotPos,rot);
	AIMcameraState.SetHeadPos(m_HeadPos);
	g_camera2D->Update();
	g_camera3D->Update();

}