#include "stdafx.h"
#include "AnimationPlayController.h"

namespace Engine {
	//����������
	void AnimationPlayController::Init(Skeleton* skeleton, int footStepBoneNo)
	{
		m_footstepBoneNo = footStepBoneNo;
		int numBones = skeleton->GetNumBones();
		//�{�[���s����m��
		m_boneMatrix.resize(numBones);
		m_skeleton = skeleton;
	}
}