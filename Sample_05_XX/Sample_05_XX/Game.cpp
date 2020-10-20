#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	m_animClip[0].Load("Assets/animData/idle.tka");
	m_animClip[0].SetLoopFlag(true);
	g_camera3D->SetPosition({ 0.0f, 100.0f, 500.0f });
	g_camera3D->SetTarget({ 0.0f, 0.0f, 0.0f });
	g_camera3D->Update();
}

Game::~Game()
{

}


bool Game::Start()
{
	//ライトを用意する。
	light.directionalLight[0].color.x = 1.0f;
	light.directionalLight[0].color.y = 1.0f;
	light.directionalLight[0].color.z = 1.0f;

	light.directionalLight[0].direction.x = 1.0f;
	light.directionalLight[0].direction.y = 0.0f;
	light.directionalLight[0].direction.z = 0.0f;

	light.ambinetLight.x = 1.0f;
	light.ambinetLight.y = 1.0f;
	light.ambinetLight.z = 1.0f;
	light.eyePos = g_camera3D->GetPosition();
	light.specPow = 5.0f;

	MR = Engine::NewGO<Engine::prefab::ModelRender>(1, nullptr);
	MR->SetTkmFilePath("Assets/modelData/unityChan.tkm");

	//スケルトンとアニメーションの初期化
	m_skeleton.Init("Assets/modelData/unityChan.tks"); 
	m_skeleton.Update(Matrix::Identity);
	m_animation.Init(m_skeleton, m_animClip, 2);
	m_animation.Play(0);
	RC = g_graphicsEngine->GetRenderContext();
	m_unityChanInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	m_unityChanInitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	m_unityChanInitData.m_vsEntryPointFunc = "VSMainSkin";
	m_unityChanInitData.m_expandConstantBuffer = &light;
	m_unityChanInitData.m_expandConstantBufferSize = (sizeof(light));

	m_mapInitData.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	m_mapInitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	m_mapInitData.m_vsEntryPointFunc = "VSMain";
	m_mapInitData.m_expandConstantBuffer = &light;
	m_mapInitData.m_expandConstantBufferSize = (sizeof(light));

	//m_unityChan.BindSkeleton(m_skeleton);

	//m_map.Init(m_mapInitData);
	//m_map.SetShadowRecieverFlag(true);
	//m_unityChan.Init(m_unityChanInitData);
	//m_skeleton.Update(m_unityChan.GetWorldMatrix());

	qrot.SetRotationDeg(Vector3::AxisX, 90.0f);
	return true;
}

void Game::Update()
{
	if (GetAsyncKeyState(VK_UP))
	{
		pos.z -= 1.0f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		pos.z += 1.0f;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		pos.x -= 1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		pos.x += 1.0f;
	}
	m_animation.Update(1.0f / 60.0f);
	//m_skeleton.Update(m_unityChan.GetWorldMatrix());
	//m_unityChan.UpdateWorldMatrix(pos, g_quatIdentity, scale);

	//m_map.UpdateWorldMatrix({0.0f,-10.0f,0.0f}, qrot, { 5.0f,5.0,1.0f });
	//g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_unityChan);
}

void Game::Draw()
{
	//m_unityChan.Draw(RC); 
	//m_map.Draw(RC, g_camera3D->GetViewMatrix(), g_camera3D->GetProjectionMatrix());
}