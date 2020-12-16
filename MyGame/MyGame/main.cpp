#include "stdafx.h"
#include "system/system.h"
#include "Game/Game.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "SourceFile/EngineProcessing.h"
#include "SourceFile/graphic/PostEffect/DefferdRendering.h"
//ゲームの時間関係
#include "SourceFile/Timer/StopWatch.h"
#include "SourceFile/Timer/GameTime.h"
#include "SourceFile/level/Level.h"

#include "Game/Test.h"

GameTime g_gameTime;
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////
	Level m_level;
	m_level.Init("Assets/Level/Map.tkl",nullptr);
	Game* g_game = nullptr;
	g_game = Engine::NewGO<Game>(0, nullptr);
	Test* m_Test = nullptr;
	//m_Test = Engine::NewGO<Test>(0, nullptr);
	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	EngineProcessing EP;
	EP.Init();

	g_graphicsEngine->GetLightManager()->InitCB();
	DirectionalLight DL1;
	DL1.direction = { 1.0f,-1.0f,-1.0f };
	DL1.direction.Normalize();
	DL1.color = {10.8f,10.8f,10.8f,1.0f};

/*	DirectionalLight DL2;
	DL2.direction = { 1.0f,1.0f,-1.0f };
	DL2.direction.Normalize();
	DL2.color = { 0.2f,0.2f,0.2f,1.0f };

	DirectionalLight DL3;
	DL3.direction = { 0.0f,0.0f,1.0f };
	DL3.direction.Normalize();
	DL3.color = { 0.2f,0.2f,0.2f,1.0f };

	DirectionalLight DL4;
	DL4.direction = { 0.0f,1.0f,0.0f };
	DL4.direction.Normalize();
	DL4.color = { 0.2f,0.2f,0.2f,1.0f };*/

	g_graphicsEngine->GetLightManager()->AddDirectionLight(DL1);
/*	g_graphicsEngine->GetLightManager()->AddDirectionLight(DL2);
	g_graphicsEngine->GetLightManager()->AddDirectionLight(DL3);
	g_graphicsEngine->GetLightManager()->AddDirectionLight(DL4);*/

	g_graphicsEngine->GetLightManager()->SetLightAmbinetLight({ 1.2f,1.2f,1.2f });
	//g_graphicsEngine->GetLightManager()->SetLightEyepos(g_camera3D->GetPosition());
	g_graphicsEngine->GetLightManager()->SetLightSpecpow(5.0f);

	DefferdRendering DR;
	g_graphicsEngine->GetDefferdRendering()->CreateRT();

	StopWatch sw;
	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//カメラのアップデート
		g_camera2D->Update();
		g_camera3D->Update();
		g_graphicsEngine->GetLightManager()->SetLightEyepos(g_camera3D->GetPosition());


		//ストップウォッチの計測開始
		sw.Start();

		EP.Update();
		

		//レンダリング開始。
		g_engine->BeginFrame();
		EP.Rendering();
		g_graphicsEngine->GetDefferdRendering()->DrawRT();

		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		//レンダリング終了。
		g_engine->EndFrame();

		//ストップウォッチの計測終了
		sw.Stop();

		//このフレームにかかった時間を記憶しておく
		g_gameTime.PushFrameDeltaTime(sw.GetElapsed());
		float f = g_gameTime.GetFPS();
	}
	
	if (g_game != nullptr)
	{
		DeleteGO(g_game);
	}
	if (m_Test != nullptr)
	{
		DeleteGO(m_Test);
	}
	Engine::GameObjectManager().DeleteAllGameObject();
	return 0;
}