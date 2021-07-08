#pragma once
#include "MapChipRender.h"
#include "SourceFile/Physics/PhysicsStaticObject.h"

struct LevelObjectData;
class MapChip:Noncopyable
{
public:
	MapChip(const LevelObjectData& objData,MapChipRender*mapChipRender);
	~MapChip()
	{
	}

private:
	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g
};

