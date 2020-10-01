#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	m_animClip[0].Load("Assets/animData/run.tka");
	m_animClip[0].SetLoopFlag(true);
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
	
	//スケルトンとアニメーションの初期化
	m_skeleton.Init("Assets/modelData/unityChan.tks"); 
	m_skeleton.Update(Matrix::Identity);
	m_animation.Init(m_skeleton, m_animClip, 2);
	m_animation.Play(0);
	RC = g_graphicsEngine->GetRenderContext();
	m_unityChanInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	m_unityChanInitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	m_unityChanInitData.m_vsEntryPointFunc = "VSMain";
	m_unityChanInitData.m_expandConstantBuffer = &light;
	m_unityChanInitData.m_expandConstantBufferSize = (sizeof(light));
	m_unityChan.Init(m_unityChanInitData);
	m_unityChan.BindSkeleton(m_skeleton);
	m_skeleton.Update(m_unityChan.GetWorldMatrix());

	return true;
}

void Game::Update()
{
	m_animation.Update(1.0f / 30.0f);
	m_unityChan.UpdateWorldMatrix(pos, g_quatIdentity, scale);
}

void Game::Draw()
{
	m_unityChan.Draw(RC);
}