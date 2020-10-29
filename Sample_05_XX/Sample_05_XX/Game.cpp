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
	if (m_unityChan != nullptr)
	{
		DeleteGO(m_unityChan);
		m_unityChan = nullptr;
	}
	if (m_map != nullptr)
	{
		DeleteGO(m_map);
		m_map = nullptr;
	}
}


bool Game::Start()
{
	m_unityChan = Engine::NewGO<Engine::prefab::ModelRender>(1, nullptr);
	m_unityChan->SetTkmFilePath("Assets/modelData/unityChan.tkm");
	m_unityChan->SetVSEntryPoint("VSMainSkin");
	m_unityChan->SetSkeleton(m_skeleton);
	Quaternion q_rot = Quaternion::Identity;
	q_rot.SetRotationDeg(Vector3::AxisX, 90.0f);
	m_unityChan->SetRotation(q_rot);

	m_map = Engine::NewGO<Engine::prefab::ModelRender>(2, nullptr);
	m_map->SetTkmFilePath("Assets/modelData/bg/bg.tkm");
	m_map->SetVSEntryPoint("VSMain");
	//m_map->SetPSEntryPoint("PSMain");
	m_map->SetShadowRecieverFlag(true);
	m_map->SetShadowCasterFlag(false);
	
	//m_unityChanInitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	//m_unityChanInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";

	//スケルトンとアニメーションの初期化
	m_skeleton.Init("Assets/modelData/unityChan.tks"); 
	m_skeleton.Update(Matrix::Identity);
	m_animation.Init(m_skeleton, m_animClip, 1);
	m_animation.Play(0);
	//RC = g_graphicsEngine->GetRenderContext();
	//m_unityChan.Init(m_unityChanInitData);
	return true;
}

void Game::Update()
{
	m_animation.Update(1.0f / 60.0f);
	if (GetAsyncKeyState(VK_UP))
	{
		pos.y -= 1.0f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		pos.y += 1.0f;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		pos.x -= 1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		pos.x += 1.0f;
	}

	m_unityChan->SetPosition(pos);
}

void Game::Draw()
{
	//m_unityChan.Draw(g_graphicsEngine->GetRenderContext());

}