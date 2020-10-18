#pragma once
#include "Noncopyable.h"

class EngineProcessing:public Noncopyable
{
public:
	EngineProcessing()
	{
	}
	~EngineProcessing()
	{
	}

	void Init();
	void Update();
	void Rendering();
};

