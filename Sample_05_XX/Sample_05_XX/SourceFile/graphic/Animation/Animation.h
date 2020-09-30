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

		//初期化処理
		//skeleton		スケルトン
		void Init(Skeleton& skeleton);
	};
}