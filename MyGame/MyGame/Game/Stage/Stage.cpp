#include "stdafx.h"
#include "Stage.h"
#include "SourceFile/level/Level.h"
#include "Grass/Grass_03.h"
#include "Tree/Tree1.h"
#include "Tree/Tree2.h"
#include "Bush/Bush_02.h"
#include "Path.h"
#include "SourceFile/Sound/SoundSource.h"
#include "Game/Player/Player.h"
#include "Game/Enemy/Enemy.h"

Stage::Stage()
{
	if (m_level == nullptr)
	{
		m_level = new Level();
		m_sound = NewGO<SoundSource>(0);
		//熱帯の環境音を初期化
		m_sound->Init(L"Assets/sound/Environmental_sound_Tropical.wav");
		//ループで再生する
		m_sound->Play(true);
	}
	m_level->Init("Assets/Level/Map.tkl", [&](const LevelObjectData& objData) {
		if (wcscmp(objData.name, L"Player") == 0)
		{
			m_Player = NewGO<Player>(0);
			m_Player->SetPosition(objData.position);
			m_Player->SetRotation(objData.rotation);
			return true;
		}
		else if (wcscmp(objData.name, L"SM_Grass_03") == 0)
		{	
			//草
			if (m_Glass == nullptr)
			{
				m_Glass = NewGO<Grass_03>(0);
				m_Glass->InitInstance(objData.position, objData.rotation, objData.scale);
			}
			else
			{
				m_Glass->AddInstance(objData.position, objData.rotation, objData.scale);
			}
			return true;
		}
		else if (wcscmp(objData.name, L"SM_Tree_Tropic_02_novines") == 0)
		{
			//木
			if (m_Tree1 == nullptr)
			{
				m_Tree1 = NewGO<Tree1>(0);
				m_Tree1->InitInstance(objData.position, objData.rotation, objData.scale);
			}
			else
			{
				m_Tree1->AddInstance(objData.position, objData.rotation, objData.scale);
			}
			return true;
		}
		else if (wcscmp(objData.name, L"SM_Tree_Tropic_02") == 0)
		{
			//木
			if (m_Tree2 == nullptr)
			{
				m_Tree2 = NewGO<Tree2>(0);
				m_Tree2->InitInstance(objData.position, objData.rotation, objData.scale);
			}
			else
			{
				m_Tree2->AddInstance(objData.position, objData.rotation, objData.scale);
			}
			return true;
		}
		else if (wcscmp(objData.name, L"SM_BushA_02") == 0)
		{
			//木
			if (m_Bush == nullptr)
			{
				m_Bush = NewGO<Bush_02>(0);
				m_Bush->InitInstance(objData.position, objData.rotation, objData.scale);
			}
			else
			{
				m_Bush->AddInstance(objData.position, objData.rotation, objData.scale);
			}
			return true;
		}
		for (int i = 0; i < 100; i++)
		{
			wchar_t m_pathchar[256] = L"Path_";
			if (Firstplace == 10)
			{
				//10の位に上げる
				Tenthplace++;
				Firstplace = 0;
			}
			wchar_t first[2];
			wchar_t ten[2];			
			_itow_s(Firstplace, first, 10);
			_itow_s(Tenthplace, ten, 10);
			//10の位をファイルパスに結合
			wcscat_s(m_pathchar, ten);
			//1の位をファイルパスに結合
			wcscat_s(m_pathchar, first);
			////_をファイルパスに結合
			//wcscat_s(m_pathchar, L"_");
			//カウントを1上げる
			Firstplace++;
			if (wcsncmp(objData.name, m_pathchar, 7) == 0)
			{
				//ファイルパスが合致したとき
				if (m_IsPathInited[m_numPath] == false)
				{
					m_IsPathInited[m_numPath] = true;
					m_Path.push_back(new Path());
				}
				m_Path[m_numPath]->AddPosition(objData.position);
				//10の位を0に戻す
				Tenthplace = 0;
				//1の位を0に戻す
				Firstplace = 0;
				//パスの数を0に戻す
				m_numPath = 0;
				return true;
			}
			m_numPath++;
		}
		Tenthplace = 0;
		Firstplace = 0;
		m_numPath = 0;
		for (int i = 0; i < 100; i++)
		{
			wchar_t m_enemychar[256] = L"Enemy_";
			if (Firstplace == 10)
			{
				//10の位に上げる
				Tenthplace++;
				Firstplace = 0;
			}
			wchar_t first[2];
			wchar_t ten[2];
			_itow_s(Firstplace, first, 10);
			_itow_s(Tenthplace, ten, 10);
			//10の位をファイルパスに結合
			wcscat_s(m_enemychar, ten);
			//1の位をファイルパスに結合
			wcscat_s(m_enemychar, first);
			////_をファイルパスに結合
			//wcscat_s(m_enemychar, L"_");
			//カウントを1上げる
			Firstplace++;

			if (wcsncmp(objData.name, m_enemychar, 8) == 0)
			{
				//ファイルパスが合致したとき
				if (m_IsEnemyInited[m_numEnemy] == false)
				{
					m_IsEnemyInited[m_numEnemy] = true;
					m_enemy.push_back(NewGO<Enemy>(0));
				}
				
				//エネミーのポジションをセット
				m_enemy[m_numEnemy]->SetPosition(objData.position);
				//エネミーの回転をセット
				m_enemy[m_numEnemy]->SetRotation(objData.rotation);

				//10の位を0に戻す
				Tenthplace = 0;
				//1の位を0に戻す
				Firstplace = 0;
				//パスの数を0に戻す
				m_numEnemy = 0;

				return true;
			}
			m_numEnemy++;
		}
		Tenthplace = 0;
		Firstplace = 0;
		m_numEnemy = 0;

		return false;
	});

	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->SetPath(m_Path[i]);
	}
}

Stage::~Stage()
{
	if (m_Player != nullptr)
	{
		DeleteGO(m_Player);
		m_Player = nullptr;
	}
	if (m_level != nullptr)
	{
		delete m_level;
		m_level = nullptr;
	}
	if (m_sound != nullptr)
	{
		DeleteGO(m_sound);
		m_sound = nullptr;
	}
	if (m_Glass != nullptr)
	{
		DeleteGO(m_Glass);
		m_Glass = nullptr;
	}
	if (m_Tree1 != nullptr)
	{
		DeleteGO(m_Tree1);
		m_Tree1 = nullptr;
	}
	if (m_Tree2 != nullptr)
	{
		DeleteGO(m_Tree2);
		m_Tree2 = nullptr;
	}
	if (m_Bush != nullptr)
	{
		DeleteGO(m_Bush);
		m_Bush = nullptr;
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