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
	//���݂̃V�[�����폜
	DeleteScene(m_SceneNum);
}

bool Game::Start()
{
	//�n�߂̓^�C�g���𐶐�
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
		//�^�C�g���V�[���̎�
		if (m_Title != nullptr)
		{
			//�^�C�g�����폜
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
		//��������V�[�����^�C�g���̎�
		if (m_Title == nullptr)
		{
			//�^�C�g����NewGO
			m_Title = NewGO<Title>(0);
		}
	}
	else if (scenenum == SceneNum::enScene_Stage01)
	{
		//��������V�[�����X�e�[�W01�̎�
		if (m_Stage_01 == nullptr)
		{
			//�X�e�[�W01��new
			m_Stage_01 = new Stage();
		}
	}
	m_SceneNum = scenenum;
	IsDirty = true;
}

void Game::SceneTrans(int scenenum)
{
	//���݂̃V�[�����폜
	DeleteScene(m_SceneNum);
	//���̃V�[���𐶐�
	NewScene(scenenum);
}