#include "stdafx.h"
#include "Stage.h"

Stage::Stage()
{
	//m_level.Init("Assets/Level/Map.tkl", nullptr);
	m_level.Init("Assets/Level/Map.tkl", [&](const LevelObjectData& objData) {
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
			if (m_Tree == nullptr)
			{
				m_Tree = NewGO<Tree1>(0);
				m_Tree->InitInstance(objData.position, objData.rotation, objData.scale);
			}
			else
			{
				m_Tree->AddInstance(objData.position, objData.rotation, objData.scale);
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
		return false;
	});

}

Stage::~Stage()
{

}