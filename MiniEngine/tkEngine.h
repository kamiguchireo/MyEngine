#pragma once

#include "HID/GamePad.h"
#include "SourceFile/Physics/PhysicsWorld.h"
#include "SourceFile/Sound/SoundEngine.h"

class GraphicsEngine;

class TkEngine {
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~TkEngine();
	/// <summary>
	/// �t���[���̊J�n���ɌĂ΂�鏈���B
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// �t���[���̏I�����ɌĂ΂�鏈���B
	/// </summary>
	void EndFrame();
	/// <summary>
	/// �Q�[���G���W���̏������B
	/// </summary>
	void Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight);

	//�������[���h�̎擾
	Engine::PhysicsWorld& GetPhysicsWorld()
	{
		return m_physicsWorld;
	}

	SoundEngine& GetSoundEngine()
	{
		return m_soundEngine;
	}
private:
	GraphicsEngine* m_graphicsEngine = nullptr;		//�O���t�B�b�N�G���W���B
	GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//�Q�[���p�b�h�B
	Engine::PhysicsWorld m_physicsWorld;		//�������[���h�B
	SoundEngine m_soundEngine;		//�T�E���h�G���W��
};

extern TkEngine* g_engine;	//TK�G���W���B