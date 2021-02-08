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
	MapChipRender* m_mapChipRender = nullptr;		//�}�b�v�`�b�v�����_�[
	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g
};

