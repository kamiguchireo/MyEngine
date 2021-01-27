#pragma once
#include "SourceFile/level/Level.h"
#include "Game/Grass/Grass_03.h"

class Stage
{
public:
	Stage();
	~Stage();
	
private:
	Level m_level;
	Grass_03* m_Glass = nullptr;
};

