#include "stdafx.h"
#include "SpriteRender.h"

namespace Engine {
	namespace prefab {
		SpriteRender::SpriteRender()
		{

		}

		SpriteRender::~SpriteRender()
		{

		}

		void SpriteRender::Update()
		{
			if (IsInited)
			{
				//‰Šú‰»Ï‚Ý‚ÌŽž
				m_sprite.Update(m_pos, m_rot, m_scale, m_pivot);
			}

		}

		void SpriteRender::PostRender()
		{
			m_sprite.Draw(g_graphicsEngine->GetRenderContext());
		}
	}
}