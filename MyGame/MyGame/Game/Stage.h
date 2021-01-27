#pragma once
#include "SourceFile/level/Level.h"
#include "Game/Glass/Glass_1.h"

class Stage
{
public:
	Stage();
	~Stage();
	
private:
	Level m_level;
	Glass_1* m_Glass = nullptr;
};

