#pragma once
#include "tkFile/tkaFile.h"

namespace Engine {
	class AnimationClip
	{
	public:
		AnimationClip();
		~AnimationClip();

		//�ǂݍ��ݏ���
		void Load(const char* filePath);
	};
}