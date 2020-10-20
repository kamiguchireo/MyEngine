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
	//Model m_unityChan;
	//Model m_map;
	ModelInitData m_mapInitData;
	ModelInitData m_unityChanInitData;
	Vector3 pos = {0.0f,0.0f,0.0f};
	Vector3 scale = Vector3::One;
	RenderContext RC;
	Light light;
	Skeleton m_skeleton;
	Engine::Animation m_animation;
	Engine::AnimationClip m_animClip[1];
	Quaternion qrot = Quaternion::Identity;
	Engine::prefab::ModelRender* MR = nullptr;
};
