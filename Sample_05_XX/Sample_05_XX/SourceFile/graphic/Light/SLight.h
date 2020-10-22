#pragma once
#include "stdafx.h"

namespace Engine {
	/// ディレクションライト。
	struct DirectionalLight {
		Vector3 direction;	//ライトの方向。
		float pad0;			//パディング。
		Vector4 color;		//ライトのカラー。
	};
}