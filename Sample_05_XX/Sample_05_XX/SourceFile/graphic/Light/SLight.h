#pragma once
#include "stdafx.h"
const int NUM_DIRECTIONAL_LIGHT = 4;	//ディレクションライトの数。

namespace Engine {
	/// ディレクションライト。
	struct DirectionalLight {
		Vector3 direction;	//ライトの方向。
		float pad0;			//パディング。
		Vector4 color;		//ライトのカラー。
	};
	/// ライト構造体。
	struct Light {
		DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];	//ディレクションライト。
		Vector3 eyePos;					//カメラの位置。
		float specPow;					//スペキュラの絞り。
		Vector3 ambinetLight;			//環境光。
	};
}