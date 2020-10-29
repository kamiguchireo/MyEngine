#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "SourceFile/EngineProcessing.h"
#include "SourceFile/graphic/DefferdRendering.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	Game* g_game = nullptr;
	g_game = Engine::NewGO<Game>(0, nullptr);
	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
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
	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		EP.Update();
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		EP.Rendering();
		g_graphicsEngine->GetDefferdRendering()->DrawRT();

		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		//�����_�����O�I���B
		g_engine->EndFrame();
	}
	
	Engine::GameObjectManager().DeleteAllGameObject();
	return 0;
}