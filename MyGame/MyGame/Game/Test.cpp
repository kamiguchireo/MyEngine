#include "stdafx.h"
#include "Test.h"

Test::Test()
{
}

Test::~Test()
{

}

void Test::OnDestroy()
{
	if (m_player != nullptr)
	{
		DeleteGO(m_player);
		m_player = nullptr;
	}
}
bool Test::Start()
{
	g_graphicsEngine->GetFade()->FadeIn();
	//m_player = NewGO<Player>(0, nullptr);
	//m_enemy = NewGO<Enemy>(0, nullptr);

	g_camera3D->SetPosition({ 0.0f,300.0f,-1000.0f });
	g_camera3D->SetTarget({ 0.0f,0.0f,0.0f });

	m_player = NewGO < prefab::ModelRender>(0);

	//ファイルパス
	m_player->SetTkmFilePath("Assets/modelData/soldier_bs01.tkm");
	m_player->SetVSEntryPoint("VSMainSkin");
	m_skeleton.Init("Assets/modelData/soldier_bs01.tks");
	m_animClip[0].Load("Assets/animData/Death_From_Front.tka");
	m_anim.Init(m_skeleton, m_animClip, 1);
	m_anim.Play(0);

	m_player->SetSkeleton(m_skeleton);
	//ポジションをセット
	m_player->SetPosition(m_pos);

	//カメラの位置に足すベクトル
	Vector3 CameraAddPos = Vector3::Zero;
	//プレイヤーの後ろ方向にカメラを引く
	CameraAddPos = m_forward * m_DeadCameraDist * -1.0f;
	CameraAddPos.y = 50.0f;
	m_DeadAfterCameraPos = m_pos + CameraAddPos;
	m_LerpForwardCameraPos = m_DeadAfterCameraPos;

	return true;
}

void Test::Update()
{
	auto deltaTime = g_gameTime.GetFrameDeltaTime();
	m_anim.Update(deltaTime);
	m_DeadLeapTime += deltaTime * m_DeadAfterLeapSpeed;
	m_DeadLeapTime = min(1.0f, m_DeadLeapTime);
	m_DeadAfterCameraPos = m_pos;
	m_DeadAfterCameraTarget = m_pos;
	//カメラの位置に足すベクトル
	Vector3 CameraAddPos = Vector3::Zero;
	//プレイヤーの後ろ方向にカメラを引く
	//CameraAddPos = m_forward * m_DeadCameraDist * -1.0f;
	CameraAddPos.y = 500.0f;
	CameraAddPos.z += 100.0f;
	m_DeadAfterCameraPos = m_pos + CameraAddPos;
	m_DeadAfterCameraPos.Lerp(m_DeadLeapTime,m_LerpForwardCameraPos, m_DeadAfterCameraPos);
	Vector3 cameradir = m_DeadAfterCameraPos - m_DeadAfterCameraTarget;
	cameradir.Normalize();
	Vector3 m_up = Cross(Vector3::Right, cameradir);

	m_rot.SetRotation(Vector3::Front, m_forward);
	m_player->SetPosition(m_pos);
	m_player->SetRotation(m_rot);
	g_camera3D->SetPosition(m_DeadAfterCameraPos);
	g_camera3D->SetTarget(m_DeadAfterCameraTarget);
	g_camera3D->SetUp(m_up);
}