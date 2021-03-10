#pragma once
#include "SourceFile/graphic/ModelRender.h"
#include "Stage/Tree/Tree2.h"

class Test:public IGameObject
{
public:
	Test();
	~Test();

	bool Start();
	void Update();
private:
	prefab::ModelRender* m_Model = nullptr;
	Tree2* m_Tree = nullptr;
};