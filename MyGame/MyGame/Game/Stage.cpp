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
				m_Glass = NewGO<Glass_1>(0);
				m_Glass->InitInstance(objData.position, objData.rotation, objData.scale);
			}
			else
			{
				m_Glass->AddInstance(objData.position, objData.rotation, objData.scale);
			}
			return true;
		}
		return false;
	});

}

Stage::~Stage()
{

}