#pragma once
#include "Player/Player.h"
#include "Enemy/Enemy.h"

class Test:public IGameObject
{
public:
	Test();
	~Test();

	void OnDestroy();
	bool Start();
	void Update();
private:
	Vector3 m_pos = { 0.0f,0.0f,0.0f };
	//Player* m_player = nullptr;
	//Enemy* m_enemy = nullptr;
	prefab::ModelRender* m_player = nullptr;
	prefab::ModelRender* m_enemy = nullptr;
	SoundSource* m_sound = nullptr;
	Vector3 m_forward = Vector3::Front;
	float rot = 0.0f;
};