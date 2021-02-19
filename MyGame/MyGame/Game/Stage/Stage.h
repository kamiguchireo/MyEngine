#pragma once
#include "SourceFile/level/Level.h"
#include "Grass/Grass_03.h"
#include "Tree/Tree1.h"
#include "Tree/Tree2.h"
#include "Bush/Bush_02.h"
#include "Pass.h"

class Stage
{
public:
	Stage();
	~Stage();
	
private:
	Level m_level;
	Grass_03* m_Glass = nullptr;
	Tree1* m_Tree1 = nullptr;
	Tree2* m_Tree2 = nullptr;
	Bush_02* m_Bush = nullptr;
	Pass* m_Pass = nullptr;
};

