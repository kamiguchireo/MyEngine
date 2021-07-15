#include "stdafx.h"
#include "GameClear.h"
#include "Game.h"

GameClear* GameClear::m_Instance = nullptr;
GameClear::GameClear()
{
	m_Instance = this;
}

GameClear::~GameClear()
{

}

void GameClear::OnDestroy()
{
	//�X�v���C�g
	if (m_ClearSprite != nullptr)
	{
		DeleteGO(m_ClearSprite);
		m_ClearSprite = nullptr;
	}
}

void GameClear::Init(Vector3 pos, Vector3 forward)
{
	m_pos = pos;
	m_forward = forward;
	m_IsInited = true;
}

bool GameClear::Start() 
{
	//�X�v���C�g�̏�����
	m_ClearSprite = NewGO<prefab::SpriteRender>(0);
	m_ClearSprite->Init("Assets/Image/Clear.dds", 600, 1500);
	m_ClearSprite->SetAlpha(m_ClearSpriteAlpha);

	m_process = ClearProcess::enProcess_PlaySound;
	return true;
}

void GameClear::Update()
{
	if (m_IsInited)
	{
		if (m_process == ClearProcess::enProcess_PlaySound)
		{
			//���̃v���Z�X��
			m_process++;
		}
		else if (m_process == ClearProcess::enProcess_CameraMove)
		{
			//���̃v���Z�X��
			m_process++;
		}
		else if (m_process == ClearProcess::enProcess_SelectScene)
		{
			//�J�ڂ���V�[����I��
			m_process++;
		}
		else if (m_process == ClearProcess::enProcess_Fade)
		{
			//�t�F�[�h�A�E�g
			g_graphicsEngine->GetFade()->FadeOut();
			m_process++;
		}
		else if (m_process == ClearProcess::enProcess_WithoutAlpha)
		{
			//�X�v���C�g�̃���
			float alpha = 1.0f - g_graphicsEngine->GetFade()->GetAlpha();
			if (alpha <= 0.001f)
			{
				//����Ȃ�0�ɋ߂��̂�0�ɂ���
				alpha = 0.0f;
				//�v���Z�X���C���N�������g
				m_process++;
			}
			m_ClearSprite->SetAlpha(alpha);
		}
		else if (m_process == ClearProcess::enProcess_SceneTrans)
		{
			//�L���X�^�[�̃N���A
			g_graphicsEngine->CasterClear();
			auto g_game = Game::GetInstance();
			//�^�C�g���Ăяo��
			g_game->SceneTrans(SceneNum::enScene_Title);
			//�V�[���J��
			m_process++;
		}

	}
}