#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "SourceFile/GameObject/GameObjectManager.h"

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

	Game* game = Engine::NewGO<Game>(0, nullptr);
	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		Engine::GameObjectManager().Start();
		Engine::GameObjectManager().PreRender();
		Engine::GameObjectManager().Update();
		g_graphicsEngine->GetShadowMap()->Update(
			{ -500.0f,1000.0f,0.0f },
			Vector3::Zero
		);
		//レンダリング開始。
		g_engine->BeginFrame();
	
		g_graphicsEngine->GetShadowMap()->RenderToShadowMap();
		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////
		//Engine::GameObjectManager().Thread();
		Engine::GameObjectManager().Draw();
		Engine::GameObjectManager().PostRender();
		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		//レンダリング終了。
		g_engine->EndFrame();
	}
	return 0;
}