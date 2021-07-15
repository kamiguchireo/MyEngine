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
	if (m_enemy != nullptr)
	{
		DeleteGO(m_enemy);
		m_enemy = nullptr;
	}
	if (m_sound != nullptr)
	{
		m_sound->Stop();
		DeleteGO(m_sound);
		m_sound = nullptr;
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
	m_enemy = NewGO < prefab::ModelRender>(1);
	m_sound = NewGO<SoundSource>(2);

	//ファイルパス
	m_player->SetTkmFilePath("Assets/modelData/soldier_bs01.tkm");
	m_enemy->SetTkmFilePath("Assets/modelData/soldier_bs01.tkm");
	m_sound->Init(L"Assets/sound/Rifle_fire.wav", true);

	//ポジションをセット
	m_player->SetPosition(m_pos);
	m_enemy->SetPosition(Vector3::Zero);
	m_sound->SetPosition(Vector3::Zero);

	return true;
}

void Test::Update()
{
	m_sound->Play(true);
	m_pos.x += g_pad[0]->GetLStickXF();
	m_pos.z += g_pad[0]->GetLStickYF();
	m_forward = Vector3::Front;
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pos.y += 1.0f;
	}
	else if (GetAsyncKeyState(VK_LCONTROL))
	{
		m_pos.y -= 1.0f;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		rot -= 0.01f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		rot += 0.01f;
	}

	if (rot >= 360.0f)
	{
		rot = 0.0f;
	}
	if (rot <= -360.0f)
	{
		rot = 0.0f;
	}
	Vector3 AddPos = Vector3::Zero;
	AddPos.x -= sinf(rot) * 100.0f;
	AddPos.z = cosf(rot) * 100.0f;
	m_forward += AddPos;

	Quaternion m_rot = Quaternion::Identity;
	m_rot.SetRotation(Vector3::Front, m_forward);

	m_player->SetPosition(m_pos);
	m_player->SetRotation(m_rot);
	g_engine->GetSoundEngine().SetListenerPosition(m_pos);
	g_engine->GetSoundEngine().SetListenerFront(m_forward);
}