#pragma once

namespace Engine
{
	class LightManager
	{
	public:
		LightManager()
		{

		}
		~LightManager()
		{

		}
	private:
		/// ���C�g�\���́B
		struct Light {
			DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];	//�f�B���N�V�������C�g�B
			Vector3 eyePos;					//�J�����̈ʒu�B
			float specPow;					//�X�y�L�����̍i��B
			Vector3 ambinetLight;			//�����B
		};
	};
}
