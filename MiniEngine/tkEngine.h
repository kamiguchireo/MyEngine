#pragma once

#include "HID/GamePad.h"
#include "SourceFile/Physics/PhysicsWorld.h"
#include "SourceFile/Sound/SoundEngine.h"

class GraphicsEngine;

class TkEngine {
public:
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~TkEngine();
	/// <summary>
	/// フレームの開始時に呼ばれる処理。
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// フレームの終了時に呼ばれる処理。
	/// </summary>
	void EndFrame();
	/// <summary>
	/// ゲームエンジンの初期化。
	/// </summary>
	void Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight);

	//物理ワールドの取得
	Engine::PhysicsWorld& GetPhysicsWorld()
	{
		return m_physicsWorld;
	}

	SoundEngine& GetSoundEngine()
	{
		return m_soundEngine;
	}
private:
	GraphicsEngine* m_graphicsEngine = nullptr;		//グラフィックエンジン。
	GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//ゲームパッド。
	Engine::PhysicsWorld m_physicsWorld;		//物理ワールド。
	SoundEngine m_soundEngine;		//サウンドエンジン
};

extern TkEngine* g_engine;	//TKエンジン。