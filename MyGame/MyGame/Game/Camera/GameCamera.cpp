#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	//TPS�J�����ɂ���
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
	g_camera2D->Update();
	g_camera3D->Update();

}