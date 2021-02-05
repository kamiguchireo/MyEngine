#include "stdafx.h"
#include "EngineProcessing.h"

void EngineProcessing::Init()
{
	//カメラを初期化
	g_camera3D->SetPosition({ 0.0f,100.0f,300.0f });
	g_camera3D->SetTarget({ 0.0f, 100.0f, 0.0f });
	//g_camera3D->SetUp(Vector3::Up);
	g_camera3D->SetFar(5000.0f);
	g_camera3D->Update();

	g_camera2D->SetPosition({ 0.0f, 0.0f, 1.0f });
	g_camera2D->SetTarget({ 0.0f, 0.0f, 0.0f });
	//g_camera2D->SetUp(Vector3::Up);
	g_camera2D->SetFar(100.0f);
	g_camera2D->Update();

	//フィジックスワールドを初期化
	g_graphicsEngine->GetPhysicsWorld().Init();
}

void EngineProcessing::Update()
{
	Engine::GameObjectManager().Start();
	Engine::GameObjectManager().PreRender();
	Engine::GameObjectManager().Update();

	//フィジックスワールドの更新
	g_graphicsEngine->GetPhysicsWorld().Update();

	//シャドウマップのアップデート
	g_graphicsEngine->GetShadowMap()->Update();
}

void EngineProcessing::Rendering()
{
	//シャドウマップの描画
	g_graphicsEngine->GetShadowMap()->RenderToShadowMap();
	g_graphicsEngine->GetLightManager()->SendLigParamToGpu();
	////ゲームオブジェクトの描画
	//Engine::GameObjectManager().Draw();
	////ゲームオブジェクトのポストレンダー
	//Engine::GameObjectManager().PostRender();
}