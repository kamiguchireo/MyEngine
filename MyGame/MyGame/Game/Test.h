#pragma once
#include "SourceFile/graphic/ModelRender.h"

class Test:public IGameObject
{
public:
	Test();
	~Test();

	bool Start();
	void Update();
private:
	prefab::ModelRender* m_Model = nullptr;

};