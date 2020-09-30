#include "stdafx.h"
#include "AnimationPlayController.h"

namespace Engine {
	//初期化処理
	void AnimationPlayController::Init(Skeleton* skeleton, int footStepBoneNo)
	{
		m_footstepBoneNo = footStepBoneNo;
		int numBones = skeleton->GetNumBones();
		//ボーン行列を確保
		m_boneMatrix.resize(numBones);
		m_skeleton = skeleton;
	}
}