#include "stdafx.h"
#include "Game.h"
#include "Stage/Stage.h"
#include "Player/Player.h"
#include "Enemy/Enemy.h"

Game* Game::m_Instance = nullptr;
Game::Game()
{
	m_Instance = this;
}

Game::~Game()
{

}

void Game::Destroy()
{
	DeleteObject();
}

bool Game::Start()
{
	m_Stage = new Stage();

	enemy = NewGO<Enemy>(0, nullptr);

	g_camera3D->SetPosition({ 0.0f, 100.0f, -300.0f });
	g_camera3D->SetTarget({ 0.0f, 100.0f, 0.0f });

	return true;
}

void Game::Update()
{
	if (IsDestroyObject)
	{
		DeleteObject();
		NewObject();
		IsDestroyObject = false;
	}
}

void Game::DeleteObject()
{
	if (m_Stage != nullptr)
	{
		delete m_Stage;
		m_Stage = nullptr;
	}
	if (enemy != nullptr)
	{
		DeleteGO(enemy);
		enemy = nullptr;
	}
}

void Game::NewObject()
{
	if (m_Stage == nullptr)
	{
		m_Stage = new Stage();
	}
	if (enemy == nullptr)
	{
		enemy = NewGO<Enemy>(0, nullptr);
	}
}
void Game::SceneTrans()
{
	IsDestroyObject = true;
}