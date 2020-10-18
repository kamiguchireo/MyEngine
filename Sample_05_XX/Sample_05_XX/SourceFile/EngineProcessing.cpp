#include "stdafx.h"
#include "EngineProcessing.h"

void EngineProcessing::Init()
{
	//カメラを初期化
	g_camera3D->SetPosition({ 0.0f,100.0f,300.0f });
	g_camera3D->SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D->SetFar(10000.0f);
	g_camera3D->Update();

	g_camera2D->SetPosition({ 0.0f, 0.0f, 0.0f });
	g_camera2D->SetTarget({ 0.0f, 0.0f, 10.0f });
	g_camera2D->SetFar(100.0f);
	g_camera2D->Update();
}

void EngineProcessing::Update()
{
	Engine::GameObjectManager().Start();
	Engine::GameObjectManager().PreRender();
	Engine::GameObjectManager().Update();

	//シャドウマップのアップデート
	g_graphicsEngine->GetShadowMap()->Update(
		{ -500.0f,1000.0f,0.0f },
		Vector3::Zero
	);
}

void EngineProcessing::Rendering()
{
	//シャドウマップの描画
	g_graphicsEngine->GetShadowMap()->RenderToShadowMap();
	//ゲームオブジェクトの描画
	Engine::GameObjectManager().Draw();
	//ゲームオブジェクトのポストレンダー
	Engine::GameObjectManager().PostRender();
}