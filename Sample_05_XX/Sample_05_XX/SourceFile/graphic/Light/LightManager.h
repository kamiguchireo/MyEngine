#pragma once
#include "SLight.h"

namespace Engine
{
	class LightManager:Noncopyable
	{
	public:
		LightManager()
		{
			//lig = new Light;
		}
		~LightManager()
		{
			//delete lig;
		}

		void InitCB()
		{
			m_CB.Init(sizeof(Light), &lig);
		}
		void AddDirectionLight(DirectionalLight DLig);

		const Light& GetLight()const
		{
			return lig;
		}

		const int GetLightSize()const
		{
			return sizeof(lig);
		}

		void SetLightEyepos(Vector3 pos)
		{
			lig.eyePos = pos;
		}

		void SetLightSpecpow(float f)
		{
			lig.specPow = f;
		}

		void SetLightAmbinetLight(Vector3 ALig)
		{
			lig.ambinetLight = ALig;
		}

		void SendLigParamToGpu()
		{
			m_CB.CopyToVRAM(lig);
		}

		ConstantBuffer& GetConstantBuffer()
		{
			return m_CB;
		}
	private:
		Light lig;
		int NowDirectionLightNum = 0;
		ConstantBuffer m_CB;
	};
}
