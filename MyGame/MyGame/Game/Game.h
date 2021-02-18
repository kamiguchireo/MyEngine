#pragma once
#include "SourceFile/graphic/Animation/Animation.h"
#include "SourceFile/graphic/Animation/AnimationClip.h"
#include "SourceFile/graphic/ModelRender.h"
#include "Player/Player.h"
#include "Stage/Stage.h"
#include "Enemy/Enemy.h"

class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();

private:
	Enemy* enemy = nullptr;
	Vector3 pos = Vector3::Zero;
	Player* player = nullptr;
	prefab::ModelRender* m_building = nullptr;
	prefab::ModelRender* m_ground = nullptr;
	Stage* m_Stage = nullptr;		//ステージ
};