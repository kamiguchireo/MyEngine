#pragma once
#include "MapChipRender.h"

struct LevelObjectData;
//class MapChipRender;
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

