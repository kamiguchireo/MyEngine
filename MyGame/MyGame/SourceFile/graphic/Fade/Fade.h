#pragma once
#include "SourceFile/Graphic/SpriteRender.h"

namespace Engine {
	class Fade
	{
	public:
		Fade();
		~Fade();

		bool Init();
		void Update();
		//フェードイン
		void FadeIn();
		//フェードアウト
		void FadeOut();
		//フェードスピードを変更
		void SetFadeSpeed(float f)
		{
			m_FadeSpeed = f;
		}
		//フェード完了済みかどうか
		bool IsEnded()const
		{
			return m_IsDirty;
		}
		float GetAlpha()
		{
			return m_Alpha;
		}
	private:
		prefab::SpriteRender* m_sprite = nullptr;		//スプライト
		bool m_IsDirty = false;		//更新が必要かどうかのフラグ
		float m_FadeSpeed = 0.2f;		//フェードスピード
		float m_Alpha = 0.0f;		//現在のα
		float m_NextAlpha = 0.0f;		//次のα
		float interpolate = 0.0f;		//補完率
	};
}