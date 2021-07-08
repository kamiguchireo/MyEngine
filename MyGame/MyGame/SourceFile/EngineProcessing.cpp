#include "stdafx.h"
#include "EngineProcessing.h"

void EngineProcessing::Init()
{
	//�J������������
	g_camera3D->SetPosition({ 0.0f,100.0f,300.0f });
	g_camera3D->SetTarget({ 0.0f, 100.0f, 0.0f });
	//g_camera3D->SetUp(Vector3::Up);
	g_camera3D->SetFar(1000000.0f);
	g_camera3D->Update();

	g_camera2D->SetPosition({ 0.0f, 0.0f, 1.0f });
	g_camera2D->SetTarget({ 0.0f, 0.0f, 0.0f });
	//g_camera2D->SetUp(Vector3::Up);
	g_camera2D->SetFar(100.0f);
	g_camera2D->Update();

	//�t�B�W�b�N�X���[���h��������
	g_engine->GetPhysicsWorld().Init();
	//���C�g�}�l�[�W���[�̏�����
	g_graphicsEngine->GetLightManager()->InitCB();
	//�V���h�E�}�b�v�̏�����
	g_graphicsEngine->GetShadowMap()->ShadowMapRTCreate();
	//�f�J�[���̏�����
	g_graphicsEngine->GetDecale()->Init();
	//�X�J�C�L���[�u�̏�����
	g_graphicsEngine->GetSky()->Init();

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

	//�X�J�C�L���[�u�̃A�b�v�f�[�g
	g_graphicsEngine->GetSky()->Update();

	Engine::GameObjectManager().ExecuteDeleteGameObjects();
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