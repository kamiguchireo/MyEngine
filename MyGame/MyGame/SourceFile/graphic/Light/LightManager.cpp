#include "stdafx.h"
#include "LightManager.h"

namespace Engine {
	void LightManager::AddDirectionLight(DirectionalLight DLig)
	{
		if (NowDirectionLightNum > 4)
		{
			//����ȏド�C�g�𑝂₹�܂���
			std::abort();
		}
		lig.directionalLight[NowDirectionLightNum] = DLig;
		NowDirectionLightNum++;
	}
}