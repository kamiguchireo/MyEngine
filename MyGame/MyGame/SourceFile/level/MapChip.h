#pragma once
#include "MapChipRender.h"
#include "Level.h"

class MapChip:Noncopyable
{
public:
	MapChip(const LevelObjectData& objData,MapChipRender*mapChipRender);
	~MapChip()
	{
	}

private:
	MapChipRender* m_mapChipRender = nullptr;		//マップチップレンダー
};

