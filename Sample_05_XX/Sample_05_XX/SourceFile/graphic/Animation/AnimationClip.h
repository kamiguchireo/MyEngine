#pragma once
#include "tkFile/tkaFile.h"

namespace Engine {
	class AnimationClip
	{
	public:
		AnimationClip();
		~AnimationClip();

		//読み込み処理
		void Load(const char* filePath);
	};
}