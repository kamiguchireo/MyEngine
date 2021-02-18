#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	enemy = NewGO<Enemy>(0, nullptr);
	player = NewGO<Player>(0, nullptr);
	m_Stage = new Stage();
}

Game::~Game()
{
	//if (player != nullptr)
	//{
	//	DeleteGO(player);
	//	player = nullptr;
	//}
	if (m_Stage != nullptr)
	{
		delete m_Stage;
		m_Stage = nullptr;
	}
}


bool Game::Start()
{
	g_camera3D->SetPosition({ 0.0f, 100.0f, -300.0f });
	g_camera3D->SetTarget({ 0.0f, 100.0f, 0.0f });

	return true;
}

void Game::Update()
{

}