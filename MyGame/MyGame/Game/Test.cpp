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
		DeleteGO(m_sound);
		m_sound = nullptr;
	}
}
bool Test::Start()
{
	//m_player = NewGO<Player>(0, nullptr);
	//m_enemy = NewGO<Enemy>(0, nullptr);

	g_camera3D->SetPosition({ 0.0f,300.0f,-1000.0f });
	g_camera3D->SetTarget({ 0.0f,300.0f,0.0f });

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
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pos.y += 1.0f;
	}
	else if (GetAsyncKeyState(VK_LCONTROL))
	{
		m_pos.y -= 1.0f;
	}
	m_player->SetPosition(m_pos);
	g_engine->GetSoundEngine().SetListenerPosition(m_pos);
}