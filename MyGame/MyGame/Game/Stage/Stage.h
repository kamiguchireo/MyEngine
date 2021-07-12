#pragma once
#include "SourceFile/level/Level.h"
#include "Grass/Grass_03.h"
#include "Tree/Tree1.h"
#include "Tree/Tree2.h"
#include "Bush/Bush_02.h"
#include "Path.h"
#include "SourceFile/Sound/SoundSource.h"

class Stage
{
public:
	Stage();
	~Stage();
	
private:
	Level* m_level = nullptr;
	Grass_03* m_Glass = nullptr;
	Tree1* m_Tree1 = nullptr;
	Tree2* m_Tree2 = nullptr;
	Bush_02* m_Bush = nullptr;
	Path* m_Path = nullptr;
	SoundSource* m_sound = nullptr;
};

