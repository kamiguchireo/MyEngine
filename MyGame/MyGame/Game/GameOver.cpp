#include "stdafx.h"
#include "GameOver.h"
#include "SourceFile/sound/SoundSource.h"

GameOver* GameOver::m_Instance = nullptr;
GameOver::GameOver()
{
	m_Instance = this;
}

GameOver::~GameOver()
{

}

void GameOver::OnDestroy()
{
	//スプライト
	if (m_DeadSprite != nullptr)
	{
		DeleteGO(m_DeadSprite);
		m_DeadSprite = nullptr;
	}
	if (m_DeadSound != nullptr)
	{
		m_DeadSound->Stop();
		DeleteGO(m_DeadSound);
		m_DeadSound = nullptr;
	}
}

void GameOver::Init(Vector3 pos,Vector3 forward)
{
	m_pos = pos;
	m_forward = forward;
	m_IsInited = true;
}

bool GameOver::Start()
{
	//スプライトの初期化
	m_DeadSprite = NewGO<prefab::SpriteRender>(4, nullptr);
	m_DeadSprite->Init("Assets/Image/Died.dds", 600, 1500);
	m_DeadSprite->SetAlpha(m_DeadSpriteAlpha);
	//次はサウンド
	m_DeadSound = NewGO<SoundSource>(0);
	m_DeadSound->Init(L"Assets/sound/GameOver.wav");
	m_process = DeadProcess::enProcess_PlaySound;
	return true;
}

void GameOver::Update()
{
	if (m_IsInited)
	{
		auto deltaTime = g_gameTime.GetFrameDeltaTime();
		if (m_process == DeadProcess::enProcess_PlaySound)
		{
			//サウンドをワンショットで再生
			m_DeadSound->Play(false, false);
			//次のプロセスへ
			m_process++;
		}
		else if (m_process == DeadProcess::enProcess_CameraMove)
		{
			//ゲームオーバー時のカメラの動き
			m_DeadSpriteAlpha += m_DeadAlphaFadeSpeed * deltaTime;
			m_DeadSprite->SetAlpha(m_DeadSpriteAlpha);

			m_DeadLeapTime += deltaTime * m_DeadAfterLeapSpeed;
			m_DeadLeapTime = min(1.0f, m_DeadLeapTime);
			float f = static_cast<float>(pow(m_DeadLeapTime, 2));
			if (f >= 1.0f)
			{
				f = 1.0f;
				//次のプロセスへ
				m_process++;
			}
			//最終的なカメラの位置に足すベクトル
			Vector3 CameraAddPos = Vector3::Zero;
			//前方向を加算
			CameraAddPos = m_forward * 100.0f;
			//カメラのターゲットを前方向に加算
			m_DeadAfterCameraTarget = m_pos + CameraAddPos;
			//高さを加算
			CameraAddPos.y = 500.0f;
			//少し後ろにする
			CameraAddPos -= m_forward;
			//最終的なカメラの位置
			m_DeadAfterCameraPos = m_pos + CameraAddPos;
			//プレイヤーの後ろ方向に補完前のカメラを引く
			m_LerpForwardCameraPos = m_pos + (m_forward * m_DeadCameraDist * -1.0f);
			m_LerpForwardCameraPos.y = 50.0f;
			//補完する
			m_LerpForwardCameraPos.Lerp(f, m_LerpForwardCameraPos, m_DeadAfterCameraPos);
			//上方向の計算
			Vector3 cameradir = m_DeadAfterCameraTarget - m_LerpForwardCameraPos;
			if (cameradir.Length() != 0.0f)
			{
				cameradir.Normalize();
			}
			Vector3 right = Cross(Vector3::Up, cameradir);
			if (right.Length() != 0.0f)
			{
				right.Normalize();
			}
			Vector3 m_up = Cross(cameradir, right);
			//カメラの各設定をセット
			g_camera3D->SetPosition(m_LerpForwardCameraPos);
			g_camera3D->SetTarget(m_DeadAfterCameraTarget);
			g_camera3D->SetUp(m_up);
		}
		else if (m_process == DeadProcess::enProcess_SelectScene)
		{
			m_ToTitleTime += deltaTime;
			if (m_ToTitleTime >= 10.0f)
			{
				//60秒後
				m_NextSceneNum = SceneNum::enScene_Title;
				m_process++;
			}
			else if (GetKeyState(VK_LBUTTON))
			{
				m_NextSceneNum = SceneNum::enScene_Stage01;
				m_process++;
			}
		}
		else if (m_process == DeadProcess::enProcess_Fade)
		{
			//フェードアウト
			g_graphicsEngine->GetFade()->FadeOut();
			m_process++;
		}
		else if (m_process == DeadProcess::enProcess_WithoutAlpha)
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
			m_DeadSprite->SetAlpha(alpha);
		}

		else if (m_process == DeadProcess::enProcess_SceneTrans)
		{
			g_graphicsEngine->CasterClear();
			auto g_game = Game::GetInstance();
			//ステージ01呼び出し
			g_game->SceneTrans(m_NextSceneNum);
			//シーン遷移
			m_process++;
		}
	}
}