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
	currentState->Update(m_pos, m_target);
}