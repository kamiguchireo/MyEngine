#pragma once
#include "Game/Weapon.h"
#include "SourceFile/Graphic/SpriteRender.h"

class Level;
class Tree1;
class Tree2;
class SoundSource;
class Title : public IGameObject
{
public:
	Title() {}
	~Title();

	void OnDestroy();
	bool Start();
	void Update();
	void CameraMove();
private:
	Level* m_level = nullptr;
	Tree1* m_Tree1 = nullptr;
	Tree2* m_Tree2 = nullptr;
	prefab::ModelRender* m_skinModel = nullptr;
	Skeleton m_skeleton;		//スケルトン
	Weapon* m_weapon = nullptr;
	Vector3 m_pos = Vector3::Zero;		//キャラクターの位置
	Quaternion m_rot = Quaternion::Identity;		//キャラクターの回転
	Engine::Animation m_animation;		//アニメーション
	Engine::AnimationClip m_animClip[enTitleCharacterAnimation_Num];		//アニメーションクリップ
	Vector3 m_CameraPos = Vector3::Zero;
	Vector3 m_CameraTarget = Vector3::Zero;
	Vector3 m_CameraUp = { 0.0f,1.0f,0.0f };
	bool IsEnterGame = false;
	SoundSource* m_FireSound = nullptr;
	bool IsPlayFireSound = false;
	prefab::SpriteRender* m_sprite = nullptr;
};