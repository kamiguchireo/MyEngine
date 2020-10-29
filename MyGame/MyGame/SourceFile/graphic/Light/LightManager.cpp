#include "stdafx.h"
#include "LightManager.h"

namespace Engine {
	void LightManager::AddDirectionLight(DirectionalLight DLig)
	{
		if (NowDirectionLightNum > 4)
		{
			//‚±‚êˆÈãƒ‰ƒCƒg‚ğ‘‚â‚¹‚Ü‚¹‚ñ
			std::abort();
		}
		lig.directionalLight[NowDirectionLightNum] = DLig;
		NowDirectionLightNum++;
	}
}