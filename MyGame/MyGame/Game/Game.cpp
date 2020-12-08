#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	//m_animClip[0].Load("Assets/animData/idle.tka");
	//m_animClip[0].SetLoopFlag(true);
	player = NewGO<Player>(0, nullptr);
}

Game::~Game()
{
	//if (m_map != nullptr)
	//{
	//	DeleteGO(m_map);
	//	m_map = nullptr;
	//}
	if (player != nullptr)
	{
		DeleteGO(player);
	}
}


bool Game::Start()
{
	//m_unityChan = Engine::NewGO<Engine::prefab::ModelRender>(1, nullptr);
	//m_unityChan->SetTkmFilePath("Assets/modelData/unityChan.tkm");
	//m_unityChan->SetVSEntryPoint("VSMainSkin");
	//m_unityChan->SetSkeleton(m_skeleton);
	//Quaternion q_rot = Quaternion::Identity;
	//q_rot.SetRotationDeg(Vector3::AxisX, 90.0f);
	//m_unityChan->SetRotation(q_rot);
	//m_unityChan->SetPosition({ 0.0f,0.0f,-100.0f });
	//m_map = Engine::NewGO<Engine::prefab::ModelRender>(2, nullptr);
	//m_map->SetTkmFilePath("Assets/modelData/map.tkm");
	//m_map->SetVSEntryPoint("VSMain");
	//m_map->SetPSEntryPoint("PSMain");
	//m_map->SetShadowRecieverFlag(true);
	//m_map->SetShadowCasterFlag(true);
	//m_map->SetPosition({ 0.0f,0.0f,1500.0f });


	//スケルトンとアニメーションの初期化
	//m_skeleton.Init("Assets/modelData/unityChan.tks"); 
	//m_skeleton.Update(Matrix::Identity);
	//m_animation.Init(m_skeleton, m_animClip, 1);
	//m_animation.Play(0);

	m_building = NewGO<prefab::ModelRender>(1);
	m_building->SetTkmFilePath("Assets/modelData/old_building.tkm");
	g_camera3D->SetPosition({ 0.0f, 100.0f, -300.0f });
	g_camera3D->SetTarget({ 0.0f, 100.0f, 0.0f });
	//Vector3 scale = Vector3::One;
	//scale *= 5.0f;
	//m_building->SetScale(scale);
	return true;
}

void Game::Update()
{

}