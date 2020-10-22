#include "stdafx.h"
#include "LightManager.h"

namespace Engine {
	void LightManager::AddDirectionLight(DirectionalLight DLig)
	{
		if (NowDirectionLightNum > 4)
		{
			//これ以上ライトを増やせません
			std::abort();
		}
		lig.directionalLight[NowDirectionLightNum] = DLig;
		NowDirectionLightNum++;
	}
}