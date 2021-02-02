#pragma once
#include "SourceFile/level/Level.h"
#include "Grass/Grass_03.h"
#include "Tree/Tree1.h"
#include "Bush/Bush_02.h"

class Stage
{
public:
	Stage();
	~Stage();
	
private:
	Level m_level;
	Grass_03* m_Glass = nullptr;
	Tree1* m_Tree = nullptr;
	Bush_02* m_Bush = nullptr;
};

