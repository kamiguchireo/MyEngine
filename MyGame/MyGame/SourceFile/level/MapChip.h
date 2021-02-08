#pragma once
#include "MapChipRender.h"
#include "SourceFile/Physics/PhysicsStaticObject.h"

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
	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト
};

