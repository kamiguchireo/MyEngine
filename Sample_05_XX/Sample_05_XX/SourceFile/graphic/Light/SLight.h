#pragma once
#include "stdafx.h"
const int NUM_DIRECTIONAL_LIGHT = 4;	//ディレクションライトの数。

namespace Engine {
	/// ディレクションライト。
	struct DirectionalLight {
		Vector3 direction = Vector3::Right;	//ライトの方向。
		float pad0 = 0.0f;			//パディング。
		Vector4 color = {0.0f,0.0f,0.0f,0.0f};		//ライトのカラー。
	};
	/// ライト構造体。
	struct Light {
		DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];	//ディレクションライト。
		Vector3 eyePos = Vector3::Zero;					//カメラの位置。
		float specPow = 5.0f;					//スペキュラの絞り。
		Vector3 ambinetLight = Vector3::One;			//環境光。
	};
}