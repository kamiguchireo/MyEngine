#pragma once
#include "SourceFile/graphic/Animation/Animation.h"
#include "SourceFile/graphic/Animation/AnimationClip.h"
#include "SourceFile/graphic/ModelRender.h"
class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
	void Draw();

private:
	//RenderContext RC;
	Skeleton m_skeleton;
	Engine::Animation m_animation;
	Engine::AnimationClip m_animClip[1];
	Engine::prefab::ModelRender* m_unityChan = nullptr;
	Engine::prefab::ModelRender* m_map = nullptr;
	//Model m_unityChan;
	//ModelInitData m_unityChanInitData;
};
