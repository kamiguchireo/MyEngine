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

	void AnimationPlayController::Update(float deltaTime, Animation* animation)
	{
		if (m_animationClip == nullptr)
		{
			//�A�j���[�V�����N���b�v������܂���
			std::abort();
		}

		m_time += deltaTime;
	}

	void AnimationPlayController::ProgressKeyFrameNo(float deltaTime)
	{
		//1�t���[���O�̃L�[�t���[���ԍ����L�^���Ă���
		m_currentKeyFrameNoLastFrame = m_currentKeyFrameNo;

		const auto& topBoneKeyFrameList = m_animationClip->GetTopBoneKeyFrameList();

		//�⊮���Ԃ��i�߂Ă���
		m_interpolateTime = min(1.0f, m_interpolateTime + deltaTime);
		while (true)
		{
			//�L�[�t���[�����I�[�܂ōs�����Ƃ�
			if (m_currentKeyFrameNo >= (int)topBoneKeyFrameList.size())
			{
				//���[�v���邩?
				if (m_animationClip->IsLoop())
				{
					//���[�v
					StartLoop();
				}
			}
		}
	}

	void AnimationPlayController::StartLoop()
	{
		m_footstepPos = g_vec3Zero;
		m_currentKeyFrameNo = 0;
		m_time = 0.0f;
	}
}