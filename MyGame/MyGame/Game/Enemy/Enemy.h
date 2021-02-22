#pragma once
#include "SourceFile/graphic/ModelRender.h"
#include "SourceFile/Physics/CharacterController.h"
#include "Game/Camera/GameCamera.h"
#include "Game/Stage/Path.h"
#include "Game/Weapon.h"

class Enemy:public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();

private:
	void StopPass();
	void ChangeNextPass();
private:
	prefab::ModelRender* m_enemyModel = nullptr;		//�G�l�~�[�̃��f��
	Skeleton m_skeleton;
	Engine::Animation m_animation;		//�A�j���[�V����
	Engine::AnimationClip m_animClip[5];		//�A�j���[�V�����N���b�v
	Vector3 m_pos = { 0.0f,5.0f,-100.0f };		//�|�W�V����
	Vector3 m_scale = Vector3::One;		//�g�嗦
	Quaternion m_rot = Quaternion::Identity;		//��]��
	CharacterController characon;
	GameCamera* m_camera = nullptr;
	float rot = 0.0f;
	Path* m_path = nullptr;		//�p�X
	std::vector<Vector3> m_position;
	int m_PassSize = 0;
	int CurrentPass = 0;		//���݂̃p�X
	int NextPass = 0;		//���̃p�X
	Weapon* m_weapon = nullptr;
};