#include "stdafx.h"
#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}


bool Game::Start()
{
	//ライトを用意する。
	light.directionalLight[0].color.x = 0.5f;
	light.directionalLight[0].color.y = 0.5f;
	light.directionalLight[0].color.z = 0.5f;

	light.directionalLight[0].direction.x = 0.0f;
	light.directionalLight[0].direction.y = 0.0f;
	light.directionalLight[0].direction.z = -1.0f;

	light.ambinetLight.x = 0.2f;
	light.ambinetLight.y = 0.2f;
	light.ambinetLight.z = 0.2f;
	light.eyePos = g_camera3D->GetPosition();
	light.specPow = 5.0f;
	
	RC = g_graphicsEngine->GetRenderContext();
	m_unityChanInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	m_unityChanInitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	m_unityChanInitData.m_expandConstantBuffer = &light;
	m_unityChanInitData.m_expandConstantBufferSize = (sizeof(light));
	m_unityChan.Init(m_unityChanInitData);
	return true;
}

void Game::Update()
{
	m_unityChan.UpdateWorldMatrix(pos, g_quatIdentity, scale);
}

void Game::Draw()
{
	m_unityChan.Draw(RC);
}