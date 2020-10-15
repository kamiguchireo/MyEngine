#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "SourceFile/GameObject/GameObjectManager.h"

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

	Game* game = Engine::NewGO<Game>(0, nullptr);
	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		Engine::GameObjectManager().Start();
		Engine::GameObjectManager().PreRender();
		Engine::GameObjectManager().Update();
		g_graphicsEngine->GetShadowMap()->Update(
			{ -500.0f,1000.0f,0.0f },
			Vector3::Zero
		);
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
	
		g_graphicsEngine->GetShadowMap()->RenderToShadowMap();
		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		//Engine::GameObjectManager().Thread();
		Engine::GameObjectManager().Draw();
		Engine::GameObjectManager().PostRender();
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		//�����_�����O�I���B
		g_engine->EndFrame();
	}
	return 0;
}