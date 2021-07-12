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
		//animClips		�A�j���[�V�����N���b�v
		//numAnimClip	�A�j���[�V�����N���b�v�̐�
		void Init(Skeleton& skeleton,AnimationClip animClips[],int numAnimClip);

		//�A�j���[�V�����̍Đ�
		//clipNo		�A�j���[�V�����N���b�v�̔ԍ�
		//interpolateTime		�⊮����
		void Play(int clipNo, float interpolateTime = 0.0f)
		{
			if (clipNo < m_animationClips.size())
			{
				PlayCommon(m_animationClips[clipNo], interpolateTime);
			}
		}

		//�A�j���[�V������i�߂�
		//�G���W�������Ŏg�p���܂�
		//deltaTime		�A�j���[�V������i�߂鎞��(�P�ʁF�b)
		//�߂�l��footstep�̈ړ���
		Vector3 Update(float deltaTime);

		bool IsPlaying()
		{
			int lastPoseIndex = GetLastAnimationControllerIndex();
			return m_animationPlayController[lastPoseIndex].IsPlaying();
		}
	private:
		////////////////////////////////////
		////////�A�j���[�V�����Đ��n////////
		////////////////////////////////////

		//�A�j���[�V�����̍Đ�
		void PlayCommon(AnimationClip* nextClip, float interpolateTime);


		//���[�J���|�[�Y�̍X�V
		//deltaTime		�A�j���[�V������i�߂鎞��(�P�ʁF�b)
		void UpdateLocalPose(float deltaTime);

		//�O���[�o���|�[�Y�̍X�V
		//�߂�l��footstep�̈ړ���
		Vector3 UpdateGlobalPose();
	private:
		////////////////////////////////////////////////////
		////�A�j���[�V�����R���g���[���̃C���f�b�N�X�擾////
		////////////////////////////////////////////////////

		//�A�j���[�V�����R���g���[���̃����O�o�b�t�@��ł̃C���f�b�N�X���擾
		//startIndex		�J�n�C���f�b�N�X
		//localIndex		���[�J���C���f�b�N�X
		int GetAnimationControllerIndecx(int startIndex, int localIndex)const
		{
			return (startIndex + localIndex) % ANIMATION_PLAY_CONTROLLER_NUM;
		}
		//�ŏI�|�[�Y�ɂȂ�A�j���[�V�����̃����O�o�b�t�@��ł̃C���f�b�N�X���擾
		int GetLastAnimationControllerIndex()const
		{
			return GetAnimationControllerIndecx(m_startAnimationPlayController, m_numAnimationPlayController - 1);
		}
	private:
		static const int ANIMATION_PLAY_CONTROLLER_NUM = 32;	//!<�A�j���[�V�����R���g���[���̐��B
		Skeleton* m_skeleton = nullptr;		//�A�j���[�V������K�p����X�P���g��
		std::vector<AnimationClip*> m_animationClips;		//�A�j���[�V�����N���b�v�̔z��
		AnimationPlayController m_animationPlayController[ANIMATION_PLAY_CONTROLLER_NUM];		//�A�j���[�V�����v���C�R���g���[��
		int m_startAnimationPlayController = 0;		//�A�j���[�V�����R���g���[���̊J�n�C���f�b�N�X
		int m_numAnimationPlayController = 0;		//���ݎg�p���̃A�j���[�V�����Đ��R���g���[���̐�
		float m_interpolateTime = 0.0f;		//���݂̕⊮����
		float m_interpolateTimeEnd = 0.0f;		//�⊮�I������
		bool m_isInited = false;
		int m_footStepBoneNo = -1;		//footstep�̃{�[���ԍ�
	};
}