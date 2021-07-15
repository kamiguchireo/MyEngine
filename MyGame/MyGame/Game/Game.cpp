#include "stdafx.h"
#include "Game.h"
#include "Stage/Stage.h"
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Title/Title.h"

Game* Game::m_Instance = nullptr;
Game::Game()
{
	m_Instance = this;
}

Game::~Game()
{

}

void Game::OnDestroy()
{
	//現在のシーンを削除
	DeleteScene(m_SceneNum);
}

bool Game::Start()
{
	//始めはタイトルを生成
	m_Title = NewGO<Title>(0);
	m_SceneNum = SceneNum::enScene_Title;

	return true;
}

void Game::Update()
{
	if (IsDirty)
	{
		if (IsStageInited)
		{
			g_graphicsEngine->GetFade()->FadeIn();
			IsDirty = false;
			IsStageInited = false;
			return;
		}
		IsStageInited = true;
	}
}

void Game::DeleteScene(int scenenum)
{
	if (scenenum == SceneNum::enScene_Title)
	{
		//タイトルシーンの時
		if (m_Title != nullptr)
		{
			//タイトルを削除
			DeleteGO(m_Title);
			m_Title = nullptr;
		}
		return;
	}
	else if (scenenum == SceneNum::enScene_Stage01)
	{
		if (m_Stage_01 != nullptr)
		{
			delete m_Stage_01;
			m_Stage_01 = nullptr;
		}
		return;
	}
}

void Game::NewScene(int scenenum)
{
	if (scenenum == SceneNum::enScene_Title)
	{
		//生成するシーンがタイトルの時
		if (m_Title == nullptr)
		{
			//タイトルをNewGO
			m_Title = NewGO<Title>(0);
		}
	}
	else if (scenenum == SceneNum::enScene_Stage01)
	{
		//生成するシーンがステージ01の時
		if (m_Stage_01 == nullptr)
		{
			//ステージ01をnew
			m_Stage_01 = new Stage();
		}
	}
	m_SceneNum = scenenum;
	IsDirty = true;
}

void Game::SceneTrans(int scenenum)
{
	//現在のシーンを削除
	DeleteScene(m_SceneNum);
	//次のシーンを生成
	NewScene(scenenum);
}