#include "stdafx.h"
#include "Test.h"
#include "SourceFile/level/Level.h"
#include "Player/Player.h"
#include "Game/Stage/ReadLevelObj.h"

Test::Test()
{
	g_camera3D->SetUp(Vector3::Up);

}

Test::~Test()
{

}

void Test::OnDestroy()
{
	if (m_level != nullptr)
	{
		delete m_level;
		m_level = nullptr;
	}

	if (m_player != nullptr)
	{
		DeleteGO(m_player);
		m_player = nullptr;
	}

	for (int i = 0; i < m_Path.size(); i++)
	{
		if (m_Path[i] != nullptr)
		{
			delete m_Path[i];
			m_Path[i] = nullptr;
		}
	}
	
	for (int i = 0; i < m_enemy.size(); i++)
	{
		if (m_enemy[i] != nullptr)
		{
			DeleteGO(m_enemy[i]);
			m_enemy[i] = nullptr;
		}
	}

}
bool Test::Start()
{
	m_readobj = std::make_unique<ReadLevelObj>();
	if (m_level == nullptr)
	{
		m_level = new Level();
		m_level->Init("Assets/Level/Test.tkl",[&](const LevelObjectData& objData) {
			//プレイヤーの読み込み
			if (wcscmp(objData.name, L"Player") == 0)
			{
				m_player = NewGO<Player>(0);
				m_player->SetPosition(objData.position);

				return true;
			}
			//エネミーの使用するパスの読み込み
			bool IsPath = m_readobj->GetPathPtr(objData.name, objData.position, m_Path);
			if (IsPath == true)
			{
				return true;
			}
			//エネミーの読み込み
			auto enemy_ptr = m_readobj->GetEnemyPtr(objData.name, objData.position, objData.rotation);
			if (enemy_ptr != nullptr)
			{
				m_enemy.push_back(enemy_ptr);
				return true;
			}
			return false;
		});
	}

	//エネミーにパスをセット
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->SetPath(m_Path[i]);
	}
	
	g_graphicsEngine->GetFade()->FadeIn();

	return true;
}

void Test::Update()
{
}