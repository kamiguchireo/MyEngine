#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{

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
	m_target.y += 50.0f;
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(m_target);
}