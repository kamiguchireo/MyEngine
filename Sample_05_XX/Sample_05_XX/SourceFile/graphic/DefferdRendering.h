#pragma once
#include "Sprite.h"
namespace Engine {
	class DefferdRendering
	{
	public:
		DefferdRendering();
		~DefferdRendering();

		void CreateRT();
		void DrawRT();
		void RegistCaster(Model* Caster)
		{
			m_Casters.push_back(Caster);
		}
	private:
		static const int TexNum = 3;
		RenderTarget albedRT;
		RenderTarget normalRT;
		RenderTarget shadowRT;
		Sprite defferdLightingSprite;
		std::vector<Model*> m_Casters;		//キャスターの配列
	};
}