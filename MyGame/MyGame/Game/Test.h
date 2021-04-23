#pragma once
#include "SourceFile/Physics/PhysicsGhostObject.h"
#include "Player/Player.h"

class Test:public IGameObject
{
public:
	Test();
	~Test();

	bool Start();
	void Update();
private:
	PhysicsGhostObject m_GhostObject;
	Vector3 m_pos = Vector3::Zero;
	Player* m_model = nullptr;
};