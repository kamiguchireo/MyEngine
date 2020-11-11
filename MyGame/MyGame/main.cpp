#include "stdafx.h"
#include "system/system.h"
#include "Game/Game.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "SourceFile/EngineProcessing.h"
#include "SourceFile/graphic/DefferdRendering.h"
//ゲームの時間関係
#include "SourceFile/Timer/StopWatch.h"
#include "SourceFile/Timer/GameTime.h"

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

	Game* g_game = nullptr;
	g_game = Engine::NewGO<Game>(0, nullptr);
	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	EngineProcessing EP;
	EP.Init();

	g_graphicsEngine->GetLightManager()->InitCB();
	DirectionalLight DL;
	DL.direction = { 1.0f,0.0f,0.0f };
	DL.color = Vector4::White;
	g_graphicsEngine->GetLightManager()->AddDirectionLight(DL);
	g_graphicsEngine->GetLightManager()->SetLightAmbinetLight({ 1.0f,1.0f,1.0f });
	g_graphicsEngine->GetLightManager()->SetLightEyepos(g_camera3D->GetPosition());
	g_graphicsEngine->GetLightManager()->SetLightSpecpow(5.0f);
	//DirectionalLight DL2;
	//DL2.direction = { -1.0f,0.0f,0.0f };
	//DL2.color = {1.0f,0.0f,0.0f,0.0f};
	//g_graphicsEngine->GetLightManager()->AddDirectionLight(DL2);

	DefferdRendering DR;
	g_graphicsEngine->GetDefferdRendering()->CreateRT();

	StopWatch sw;
	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
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
	}
	
	DeleteGO(g_game);
	Engine::GameObjectManager().DeleteAllGameObject();
	return 0;
}