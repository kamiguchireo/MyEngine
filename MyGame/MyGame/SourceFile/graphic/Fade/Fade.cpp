#include "stdafx.h"
#include "Fade.h"

namespace Engine {
	Fade::Fade()
	{

	}

	Fade::~Fade()
	{

	}

	bool Fade::Init()
	{
		m_sprite = NewGO<prefab::SpriteRender>(0);
		m_sprite->Init("Assets/image/Fade.dds", g_graphicsEngine->GetFrameBufferHeight(), g_graphicsEngine->GetFrameBufferWidth());
		m_sprite->SetPosition({ 0.0f,0.0f,0.0f });
		m_sprite->SetAlpha(m_Alpha);
		return true;
	}

	void Fade::Update()
	{
		if (m_IsDirty)
		{
			if (m_Alpha != m_NextAlpha)
			{
				auto deltaTime = g_gameTime.GetFrameDeltaTime();
				if (deltaTime >= m_FadeSpeed)
				{
					interpolate += m_FadeSpeed * 0.1f;
				}
				else
				{
					interpolate += m_FadeSpeed * deltaTime;
				}
				//�⊮�����悷��
				float f = static_cast<float>(pow(interpolate, 2.0));
				if (f >= 1.0f)
				{
					//�⊮���̍ő�l��1
					f = 1.0f;
					//�X�V�I���
					m_IsDirty = false;
				}
				m_Alpha = Math::Lerp(f, m_Alpha, m_NextAlpha);
			}
			else
			{
				m_IsDirty = false;
			}
			m_sprite->SetAlpha(m_Alpha);
		}	
	}

	void Fade::FadeIn()
	{
		interpolate = 0.0f;
		m_NextAlpha = 0.0f;
		m_IsDirty = true;
	}

	void Fade::FadeOut()
	{
		interpolate = 0.0f;
		m_NextAlpha = 1.0f;
		m_IsDirty = true;
	}
}