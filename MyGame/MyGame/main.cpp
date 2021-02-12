#include "stdafx.h"
#include "system/system.h"
#include "Game/Game.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "SourceFile/EngineProcessing.h"
#include "SourceFile/graphic/PostEffect/DefferdRendering.h"
//ゲームの時間関係
#include "SourceFile/Timer/StopWatch.h"
#include "SourceFile/Timer/GameTime.h"

#include "Game/Test.h"
#include "Game/Stage/Stage.h"

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
		
	//テスト用のクラス
	//Test* m_Test = nullptr;
	//m_Test = Engine::NewGO<Test>(0, nullptr);

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	EngineProcessing EP;
	EP.Init();

	g_graphicsEngine->GetLightManager()->InitCB();
	DirectionalLight DL1;
	DL1.direction = { 1.0f,-1.0f,-1.0f };
	//DL1.direction = { 1.0f,0.0f,0.0f };
	DL1.direction.Normalize();
	DL1.color = {10.8f,10.8f,10.8f,1.0f};

	g_graphicsEngine->GetLightManager()->AddDirectionLight(DL1);

	g_graphicsEngine->GetLightManager()->SetLightAmbinetLight({ 1.2f,1.2f,1.2f });
	g_graphicsEngine->GetLightManager()->SetLightSpecpow(5.0f);

	DefferdRendering DR;
	g_graphicsEngine->GetDefferdRendering()->CreateRT();

	StopWatch sw;

	//ゲーム本体
	Game* g_game = nullptr;
	g_game = Engine::NewGO<Game>(0, nullptr);

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//カメラのアップデート
		g_camera2D->Update();
		g_camera3D->Update();

		//ライトの計算用に視点をセット
		g_graphicsEngine->GetLightManager()->SetLightEyepos(g_camera3D->GetPosition());

		//ストップウォッチの計測開始
		sw.Start();

		EP.Update();
		
		//レンダリング開始。
		g_engine->BeginFrame();
		EP.Rendering();
		g_graphicsEngine->GetDefferdRendering()->DrawRT();
		//ゲームオブジェクトの描画
		Engine::GameObjectManager().Draw();
		//ゲームオブジェクトのポストレンダー
		Engine::GameObjectManager().PostRender();

		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		//レンダリング終了。
		g_engine->EndFrame();

		//ストップウォッチの計測終了
		sw.Stop();

		//このフレームにかかった時間を記憶しておく
		g_gameTime.PushFrameDeltaTime(static_cast<float>(sw.GetElapsed()));
		float f = g_gameTime.GetFPS();
	}
	
	//ゲームの削除
	if (g_game != nullptr)
	{
		DeleteGO(g_game);
	}
	//if (m_Test != nullptr)
	//{
	//	DeleteGO(m_Test);
	//}

	return 0;
}