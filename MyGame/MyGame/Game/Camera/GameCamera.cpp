#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	//TPS�J�����ɂ���
	ChangeState(&TPScameraState);
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
	switch (m_StateNum)
	{
	case CameraState::TPS:
		//TPS�J�����ɂ���
		ChangeState(&TPScameraState);
		break;
	case CameraState::AIM:
		//AIM�J�����ɂ���
		ChangeState(&AIMcameraState);
		break;
	default:
		break;
	}
	currentState->Update(m_pos, m_target);
	g_camera2D->Update();
	g_camera3D->Update();

}