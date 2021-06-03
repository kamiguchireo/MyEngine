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

	void AnimationPlayController::Update(float deltaTime/*, Animation* animation*/)
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

		//footstep�̃{�[���̈ړ��ʂ��擾����
		SamplingDeltaValueFootStepBone();

		//�A�j���[�V�����Đ������t���O���X�P���g���ɗ��Ă�
		m_skeleton->SetMarkPlayAnimation();
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
		m_currentKeyFrameNo = 0;
		m_time = 0.0f;
		//���[�v����̂łЂƂO�̃t���[���̃t�b�g�X�e�b�v�̈ړ��ʂ����Z�b�g
		m_footstepLastValue = g_vec3Zero;
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
			if (keyframe->boneIndex < m_boneMatrix.size())
			{
				m_boneMatrix[keyframe->boneIndex] = keyframe->transform;
			}
			else
			{
				std::abort();
			}
		}
	}

	void AnimationPlayController::SamplingDeltaValueFootStepBone()
	{
		if (m_footstepBoneNo == -1)
		{
			return;
		}
		//�{�[���̐�����
		for (int boneNo = 0; boneNo < m_skeleton->GetNumBones(); boneNo++)
		{
			auto bone = m_skeleton->GetBone(boneNo);
			if (bone->GetParentBoneNo() == -1)
			{
				//���[�g�{�[���̎�
				Matrix footStepBoneWorldMatrix = Matrix::Identity;
				CalcFootStepBoneWorldMatrix(*bone, Matrix::Identity, footStepBoneWorldMatrix);
				m_footstepDeltaValue = Vector3::Zero;
				//�t�b�g�X�e�b�v����
				m_footstepDeltaValue.x = footStepBoneWorldMatrix.m[3][0];
				m_footstepDeltaValue.y = footStepBoneWorldMatrix.m[3][1];
				m_footstepDeltaValue.z = footStepBoneWorldMatrix.m[3][2];
				//�t�b�g�X�e�b�v�̈ړ��ʂ����Z
				m_boneMatrix[bone->GetNo()].m[3][0] -= footStepBoneWorldMatrix.m[3][0];
				m_boneMatrix[bone->GetNo()].m[3][1] -= footStepBoneWorldMatrix.m[3][1];
				m_boneMatrix[bone->GetNo()].m[3][2] -= footStepBoneWorldMatrix.m[3][2];
				//���̃t���[���ł̈ٓ��ʂ�m�邽�߂ɂЂƂO�̈ړ��ʂ����Z
				m_footstepDeltaValue -= m_footstepLastValue;
				//���̃t���[���Ŏg�p����ړ��ʂ���
				m_footstepLastValue.x = footStepBoneWorldMatrix.m[3][0];
				m_footstepLastValue.y = footStepBoneWorldMatrix.m[3][1];
				m_footstepLastValue.z = footStepBoneWorldMatrix.m[3][2];

				break;
			}
		}
	}

	void AnimationPlayController::CalcFootStepBoneWorldMatrix(Bone& bone, const Matrix& parentMatrix, Matrix& footStepBoneMatrix)
	{
		Matrix boneWorld = Matrix::Identity;
		Matrix localMatrix = m_boneMatrix[bone.GetNo()];
		boneWorld = localMatrix * parentMatrix;
		if (bone.GetNo() == m_footstepBoneNo)
		{
			//�t�b�g�X�e�b�v�{�[�����݂�������
			footStepBoneMatrix = boneWorld;
			return;
		}
		//�t�b�g�X�e�b�v�{�[�����݂���܂Ŏq���̃{�[���ɓK������
		for (auto childBone : bone.GetChildren())
		{
			CalcFootStepBoneWorldMatrix(*childBone, boneWorld, footStepBoneMatrix);
		}
	}
}