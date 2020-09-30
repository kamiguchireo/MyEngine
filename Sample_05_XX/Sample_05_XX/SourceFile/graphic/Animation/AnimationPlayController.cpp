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

		//�L�[�t���[���ԍ���i�߂�
		ProgressKeyFrameNo(deltaTime);

		//�{�[���s����A�j���[�V�����N���b�v����T���v�����O���Ă���
		SamplingBoneMatrixFromAnimationClip();

		//�e�̍����W�n�ɂȂ��Ă���{�[���s������[�g�̃{�[���̋�Ԃɕϊ�����
		CalcBoneMatrixInRootBoneSpace();

		//footstep�̃{�[���̈ړ��ʂ��擾����
		SamplingDeltaValueFootStepBone();
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
				else
				{
					//�����V���b�g�Đ�
					m_currentKeyFrameNo--;
					m_isPlaying = false;		//�Đ��I���
				}
				break;
			}
			if (topBoneKeyFrameList.at(m_currentKeyFrameNo)->time >= m_time)
			{
				//�I���
				break;
			}
			m_currentKeyFrameNo++;
		}
	}

	void AnimationPlayController::StartLoop()
	{
		m_footstepPos = g_vec3Zero;
		m_currentKeyFrameNo = 0;
		m_time = 0.0f;
	}

	void AnimationPlayController::SamplingBoneMatrixFromAnimationClip()
	{
		//�L�[�t���[���̔z����擾
		const auto& keyFramePtrListArray = m_animationClip->GetKeyFramePtrListArray();
		for (const auto& keyFrameList : keyFramePtrListArray)
		{
			if (keyFrameList.size() == 0)
			{
				continue;
			}
			//���ݍĐ����̃L�[�t���[�����Ƃ��Ă���
			KeyFrame* keyframe = keyFrameList.at(m_currentKeyFrameNo);
			m_boneMatrix[keyframe->boneIndex] = keyframe->transform;
		}
	}

	void AnimationPlayController::CalcBoneMatrixInRootBoneSpace()
	{
		int numBone = m_skeleton->GetNumBones();
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			//���[�g�̍�����������
			auto bone = m_skeleton->GetBone(boneNo);
			//�e�̃{�[���ԍ����擾
			if (bone->GetParentBoneNo() != -1)
			{
				continue;
			}
			CalcBoneMatrixInRootBoneSpace(*bone, g_matIdentity);
		}
	}

	void AnimationPlayController::CalcBoneMatrixInRootBoneSpace(Bone& bone, Matrix parentMatrix)
	{
		//���[���h�s����v�Z����
		//���ݍĐ����̃{�[���s����擾
		auto& mBoneInRootSpace = m_boneMatrix[bone.GetNo()];
		Matrix localMatrix = m_boneMatrix[bone.GetNo()];

		//�e�̍s��ƃ��[�J���s�����Z���āA���[���h�s����v�Z����
		mBoneInRootSpace = localMatrix * parentMatrix;

		//�q���̃��[���h�s����v�Z����
		for (auto& childBone : bone.GetChildren())
		{
			CalcBoneMatrixInRootBoneSpace(*childBone, mBoneInRootSpace);
		}
	}

	void AnimationPlayController::SamplingDeltaValueFootStepBone()
	{
		if (m_currentKeyFrameNoLastFrame == m_currentKeyFrameNo)
		{
			//�L�[�t���[�����i��ł��Ȃ��B
			return;
		}
		if (m_footstepBoneNo == -1)
		{
			return;
		}
		int numBone = m_skeleton->GetNumBones();
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			auto bone = m_skeleton->GetBone(boneNo);
			if (m_footstepBoneNo == bone->GetNo())
			{
				auto mat = m_boneMatrix[bone->GetNo()];
				Vector3 footstepBonePos;
				footstepBonePos.x = mat.m[3][0];
				footstepBonePos.x = mat.m[3][1];
				footstepBonePos.x = mat.m[3][2];
				//���̃t���[���ł�footstep�̈ړ��ʂ��v�Z����
				m_footstepDeltaValue = footstepBonePos - m_footstepPos;
				//���̃t���[���ł�footstep�̍��W���X�V����
				m_footstepPos = footstepBonePos;
				break;
			}
		}
	}
}