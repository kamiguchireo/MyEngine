#include "stdafx.h"
#include "MapChip.h"

MapChip::MapChip(const LevelObjectData& objData, MapChipRender* mapChipRender)
{
	char objName[256];
	wcstombs(objName, objData.name, 256);

	//ファイルパスを作成
	wchar_t filePath[256];
	swprintf_s(filePath, L"Assets/modelData/%s.tkm", objData.name);
	m_physicsStaticObject.CreateMesh(
		objData.position,
		objData.rotation,
		mapChipRender->GetModel()
	);
}