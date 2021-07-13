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
		else if (wcscmp(objData.name, L"Pass") == 0)
		{
			if (m_Path == nullptr)
			{
				m_Path = new Path();
				m_Path->AddPosition(objData.position);
			}
			else
			{
				m_Path->AddPosition(objData.position);
			}
			return true;
		}


		return false;
	});

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
	if (m_Path != nullptr)
	{
		delete m_Path;
		m_Path = nullptr;
	}
}