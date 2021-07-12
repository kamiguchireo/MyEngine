#include "stdafx.h"
#include "Stage.h"

Stage::Stage()
{
	if (m_level == nullptr)
	{
		m_level = new Level();
		m_sound = NewGO<SoundSource>(0);
		//îMë—ÇÃä¬ã´âπÇèâä˙âª
		m_sound->Init(L"Assets/sound/Environmental_sound_Tropical.wav");
		//ÉãÅ[ÉvÇ≈çƒê∂Ç∑ÇÈ
		m_sound->Play(true);
	}
	m_level->Init("Assets/Level/Map.tkl", [&](const LevelObjectData& objData) {
		if (wcscmp(objData.name, L"SM_Grass_03") == 0)
		{	
			//ëê
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
			//ñÿ
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
			//ñÿ
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
			//ñÿ
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