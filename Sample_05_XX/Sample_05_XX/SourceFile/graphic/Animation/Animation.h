#pragma once
#include "SourceFile/graphic/Animation/AnimationClip.h"
#include "SourceFile/graphic/Animation/AnimationPlayController.h"

class Skeleton;

namespace Engine {
	class Animation
	{
	public:
		Animation()
		{
		}
		~Animation()
		{
		}

		//����������
		//skeleton		�X�P���g��
		void Init(Skeleton& skeleton);
	};
}