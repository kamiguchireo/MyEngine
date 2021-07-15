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
	//スプライト
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
	//スプライトの初期化
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
			//次のプロセスへ
			m_process++;
		}
		else if (m_process == ClearProcess::enProcess_CameraMove)
		{
			//次のプロセスへ
			m_process++;
		}
		else if (m_process == ClearProcess::enProcess_SelectScene)
		{
			//遷移するシーンを選択
			m_process++;
		}
		else if (m_process == ClearProcess::enProcess_Fade)
		{
			//フェードアウト
			g_graphicsEngine->GetFade()->FadeOut();
			m_process++;
		}
		else if (m_process == ClearProcess::enProcess_WithoutAlpha)
		{
			//スプライトのα抜
			float alpha = 1.0f - g_graphicsEngine->GetFade()->GetAlpha();
			if (alpha <= 0.001f)
			{
				//限りなく0に近いので0にする
				alpha = 0.0f;
				//プロセスをインクリメント
				m_process++;
			}
			m_ClearSprite->SetAlpha(alpha);
		}
		else if (m_process == ClearProcess::enProcess_SceneTrans)
		{
			//キャスターのクリア
			g_graphicsEngine->CasterClear();
			auto g_game = Game::GetInstance();
			//タイトル呼び出し
			g_game->SceneTrans(SceneNum::enScene_Title);
			//シーン遷移
			m_process++;
		}

	}
}