#include "stdafx.h"
#include "EngineProcessing.h"

void EngineProcessing::Init()
{
	//�J������������
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

	//�t�B�W�b�N�X���[���h��������
	g_engine->GetPhysicsWorld().Init();
}

void EngineProcessing::Update()
{
	Engine::GameObjectManager().Start();
	Engine::GameObjectManager().PreRender();
	Engine::GameObjectManager().Update();

	//�t�B�W�b�N�X���[���h�̍X�V
	g_engine->GetPhysicsWorld().Update();

	//�V���h�E�}�b�v�̃A�b�v�f�[�g
	g_graphicsEngine->GetShadowMap()->Update();

	//�f�J�[���̃A�b�v�f�[�g
	g_graphicsEngine->GetDecale()->Update();
}

void EngineProcessing::Rendering()
{
	//�V���h�E�}�b�v�̕`��
	g_graphicsEngine->GetShadowMap()->RenderToShadowMap();
	g_graphicsEngine->GetLightManager()->SendLigParamToGpu();
	////�Q�[���I�u�W�F�N�g�̕`��
	//Engine::GameObjectManager().Draw();
	////�Q�[���I�u�W�F�N�g�̃|�X�g�����_�[
	//Engine::GameObjectManager().PostRender();
}