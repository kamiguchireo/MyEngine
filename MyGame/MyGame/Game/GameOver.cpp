#include "stdafx.h"
#include "GameOver.h"

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
	if (m_DiedSprite != nullptr)
	{
		DeleteGO(m_DiedSprite);
		m_DiedSprite = nullptr;
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
	m_DiedSprite = NewGO<prefab::SpriteRender>(4, nullptr);
	m_DiedSprite->Init("Assets/Image/Died.dds", 600, 1500);
	m_DiedSprite->SetAlpha(m_DeadSpriteAlpha);

	return true;
}

void GameOver::Update()
{
	if (m_IsInited)
	{
		auto deltaTime = g_gameTime.GetFrameDeltaTime();
		m_DeadSpriteAlpha += m_DeadAlphaFadeSpeed * deltaTime;
		m_DiedSprite->SetAlpha(m_DeadSpriteAlpha);

		m_DeadLeapTime += deltaTime * m_DeadAfterLeapSpeed;
		m_DeadLeapTime = min(1.0f, m_DeadLeapTime);
		float f = static_cast<float>(pow(m_DeadLeapTime, 2));
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
}