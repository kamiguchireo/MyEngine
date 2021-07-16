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
	//�X�v���C�g
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
	//�X�v���C�g�̏�����
	m_DeadSprite = NewGO<prefab::SpriteRender>(4, nullptr);
	m_DeadSprite->Init("Assets/Image/Died.dds", 600, 1500);
	m_DeadSprite->SetAlpha(m_DeadSpriteAlpha);
	//���̓T�E���h
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
			//�T�E���h�������V���b�g�ōĐ�
			m_DeadSound->Play(false, false);
			//���̃v���Z�X��
			m_process++;
		}
		else if (m_process == DeadProcess::enProcess_CameraMove)
		{
			//�Q�[���I�[�o�[���̃J�����̓���
			m_DeadSpriteAlpha += m_DeadAlphaFadeSpeed * deltaTime;
			m_DeadSprite->SetAlpha(m_DeadSpriteAlpha);

			m_DeadLeapTime += deltaTime * m_DeadAfterLeapSpeed;
			m_DeadLeapTime = min(1.0f, m_DeadLeapTime);
			float f = static_cast<float>(pow(m_DeadLeapTime, 2));
			if (f >= 1.0f)
			{
				f = 1.0f;
				//���̃v���Z�X��
				m_process++;
			}
			//�ŏI�I�ȃJ�����̈ʒu�ɑ����x�N�g��
			Vector3 CameraAddPos = Vector3::Zero;
			//�O���������Z
			CameraAddPos = m_forward * 100.0f;
			//�J�����̃^�[�Q�b�g��O�����ɉ��Z
			m_DeadAfterCameraTarget = m_pos + CameraAddPos;
			//���������Z
			CameraAddPos.y = 500.0f;
			//�������ɂ���
			CameraAddPos -= m_forward;
			//�ŏI�I�ȃJ�����̈ʒu
			m_DeadAfterCameraPos = m_pos + CameraAddPos;
			//�v���C���[�̌������ɕ⊮�O�̃J����������
			m_LerpForwardCameraPos = m_pos + (m_forward * m_DeadCameraDist * -1.0f);
			m_LerpForwardCameraPos.y = 50.0f;
			//�⊮����
			m_LerpForwardCameraPos.Lerp(f, m_LerpForwardCameraPos, m_DeadAfterCameraPos);
			//������̌v�Z
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
			//�J�����̊e�ݒ���Z�b�g
			g_camera3D->SetPosition(m_LerpForwardCameraPos);
			g_camera3D->SetTarget(m_DeadAfterCameraTarget);
			g_camera3D->SetUp(m_up);
		}
		else if (m_process == DeadProcess::enProcess_SelectScene)
		{
			m_ToTitleTime += deltaTime;
			if (m_ToTitleTime >= 10.0f)
			{
				//60�b��
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
			//�t�F�[�h�A�E�g
			g_graphicsEngine->GetFade()->FadeOut();
			m_process++;
		}
		else if (m_process == DeadProcess::enProcess_WithoutAlpha)
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
			m_DeadSprite->SetAlpha(alpha);
		}

		else if (m_process == DeadProcess::enProcess_SceneTrans)
		{
			g_graphicsEngine->CasterClear();
			auto g_game = Game::GetInstance();
			//�X�e�[�W01�Ăяo��
			g_game->SceneTrans(m_NextSceneNum);
			//�V�[���J��
			m_process++;
		}
	}
}