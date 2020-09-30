#include "stdafx.h"
#include "Animation.h"

namespace Engine
{
	void Animation::Init(Skeleton& skeleton, const std::vector<std::unique_ptr<AnimationClip>>&animClips)
	{
		//�A�j���[�V�����N���b�v������̎�
		if (animClips.empty() == true)
		{
			//�A�j���[�V�����N���b�v������ł�
			std::abort();
		}
		m_skeleton = &skeleton;

		//�A�j���[�V�����N���b�v�̐�������
		for (auto& animClip : animClips)
		{
			m_animationClips.push_back(animClip.get());
		}

		//footStep�{�[���̔ԍ��𒲂ׂ�
		int footsteoBoneNo = -1;
		int numBone = m_skeleton->GetNumBones();
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			auto bone = m_skeleton->GetBone(boneNo);
			//footstep�Ŗ��O����
			if (wcscmp(bone->GetName(), L"footstep") == 0)
			{
				//footstep�{�[�����݂�����
				footsteoBoneNo = boneNo;
				break;
			}
		}

		for (auto& ctr : m_animationPlayController)
		{
			ctr.Init(m_skeleton, footsteoBoneNo);
		}
	}

	//�A�j���[�V�����̍Đ�
	void Animation::PlayCommon(AnimationClip*nextClip,float interpolateTime)
	{
		if (nextClip->IsLoaded() == false)
		{
			//�A�j���[�V�����N���b�v�����[�h����Ă��܂���B
			std::abort();
		}
		//�ŏI�|�[�Y�ƂȂ�A�j���[�V�����N���b�v�̃C���f�b�N�X���擾
		int index = GetLastAnimationControllerIndex();
		//�A�j���[�V�����N���b�v��1�̎��⊮�����ɏI��
		if (m_animationPlayController[index].GetAnimClip() == nextClip)
		{
			return;
		}
		if (interpolateTime == 0.0f)
		{
			//�⊮�Ȃ�
			m_numAnimationPlayController = 1;
		}
		else 
		{
			//�⊮����
			m_numAnimationPlayController++;
		}
		index = GetLastAnimationControllerIndex();
		//�A�j���[�V�����N���b�v�̐؂�ւ�
		m_animationPlayController[index].ChangeAnimationClip(nextClip);
		m_animationPlayController[index].SetInterpolateTime(interpolateTime);
		m_interpolateTime = 0.0f;
		m_interpolateTimeEnd = interpolateTime;
	}

	//���[�J���|�[�Y�̍X�V
	void Animation::UpdateLocalPose(float deltaTime)
	{
		//�⊮���Ԃ�i�߂Ă���
		m_interpolateTime += deltaTime;
		if (m_interpolateTime >= 1.0f)
		{
			//�⊮����
			//���݂̍ŏI�A�j���[�V�����R���g���[���ւ̃C���f�b�N�X���J�n�C���f�b�N�X�ɂȂ�
			m_startAnimationPlayController = GetLastAnimationControllerIndex();
			m_numAnimationPlayController = 1;
			m_interpolateTime = 1.0f;
		}
		for (int i = 0; i < m_numAnimationPlayController - 1; i++)
		{
			int index = GetAnimationControllerIndecx(m_startAnimationPlayController, i);
			m_animationPlayController[index].Update(deltaTime, this);
		}

	}

	void Animation::Progress(float deltaTime)
	{
		if (m_numAnimationPlayController == 0)
		{
			//�A�j���[�V�����v���C�R���g���[���̐����s���ł�
			std::abort();
		}
		m_deltaTimeOnUpdate = deltaTime;
	}
}