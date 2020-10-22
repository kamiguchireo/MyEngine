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
		/// ライト構造体。
		struct Light {
			DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];	//ディレクションライト。
			Vector3 eyePos;					//カメラの位置。
			float specPow;					//スペキュラの絞り。
			Vector3 ambinetLight;			//環境光。
		};
	};
}
