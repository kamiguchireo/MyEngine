#pragma once
//�A�j���[�V�����̍Đ��R���g���[��
class Skeleton;


namespace Engine {
	class AnimationClip;
	class Animation;

	//�A�j���[�V�����̍Đ��R���g���[��
	//��̃A�j���[�V�����N���b�v�ɑ΂��ăA�j���[�V������i�߂āA
	//���[�J���|�[�Y���v�Z����
	class AnimationPlayController
	{
	public:
		AnimationPlayController()
		{
		}
		~AnimationPlayController()
		{
		}

		//������
		//skeleton		�X�P���g��
		//footStepBoneNo	footStep�̃{�[���ԍ�	
		void Init(Skeleton* skeleton, int footStepBoneNo);

		//�A�j���[�V�����N���b�v�̎擾
		AnimationClip* GetAnimClip()const
		{
			return m_animationClip;
		}

		//�A�j���[�V�����N���b�v�̕ύX
		void ChangeAnimationClip(AnimationClip* clip)
		{
			m_animationClip = clip;
			m_currentKeyFrameNo = 0;
			m_time = 0.0f;
			m_isPlaying = true;		//�Đ���
			m_footstepPos = g_vec3Zero;		//�t�b�g�X�e�b�v�̈ʒu
			m_footstepDeltaValue = g_vec3Zero;		//�t�b�g�X�e�b�v�̈ړ��x�N�g��
		}

		//�A�j���[�V�����N���b�v�̕⊮���Ԃ̐ݒ�
		void SetInterpolateTime(float interpolateTime)
		{
			if (interpolateTime < 0.0f)
			{
				//�⊮���Ԃ��s���ł�
				std::abort();
			}
			//�⊮�̏I��鎞�Ԃ�ݒ�
			m_interpolateEndTime = interpolateTime;
			//���݂̕⊮���Ԃ�ݒ�
			m_interpolateTime = 0.0f;			
		}
		//�X�V����
		//deltaTime		�A�j���[�V������i�߂鎞��
		//animation		�A�j���[�V����
		void Update(float deltaTime/*, Animation* animation*/);

		//�L�[�t���[���ԍ���i�߂�
		void ProgressKeyFrameNo(float deltaTime);

		//���[�v�Đ��J�n����Ƃ��̏���
		void StartLoop();

		//�{�[���s����A�j���[�V�����N���b�v����T���v�����O����
		void SamplingBoneMatrixFromAnimationClip();

		//���[�g�{�[����Ԃł̍s����v�Z����
		void CalcBoneMatrixInRootBoneSpace();
		//bone		�v�Z����{�[��
		//parentMatrix		�e�̍s��
		void CalcBoneMatrixInRootBoneSpace(Bone&bone,Matrix parentMatrix);

		//footstep�̃{�[���̕ω��ʂ��T���v�����O����
		void SamplingDeltaValueFootStepBone();

		//footstep�{�[���̍��W��S�̂̍����猸�Z����
		void SubtractFootstepBonePosFromAllBone();

		//�⊮�����擾
		float GetInterpolateRate()const
		{
			if (m_interpolateEndTime <= 0.0f)
			{
				return 1.0f;
			}
			return min(1.0f, m_interpolateTime / m_interpolateEndTime);
		}

		//���[�J���{�[���s����擾
		const std::vector<Matrix>& GetBoneLocalMatrix()const
		{
			return m_boneMatrix;
		}

		//Update�֐����Ăяo�������́Afootstep�{�[���̈ړ��ʂ��擾
		Vector3 GetFootStepDeltaValueOnUpdate()const
		{
			return m_footstepDeltaValue;
		}
	private:
		int m_footstepBoneNo = -1;		//�t�b�g�X�e�b�v�̃{�[���̔ԍ�
		std::vector<Matrix> m_boneMatrix;		//���̃R���g���[���ōĐ����̃A�j���[�V�����̃{�[���s��
		Skeleton* m_skeleton = nullptr;				//�X�P���g���B
		AnimationClip* m_animationClip = nullptr;		//�A�j���[�V�����N���b�v
		int m_currentKeyFrameNoLastFrame = 0;		//1�t���[���O�̃L�[�t���[���ԍ��B
		int m_currentKeyFrameNo = 0;		//���ݍĐ����̃L�[�t���[���ԍ�
		float m_time = 0.0f;
		bool m_isPlaying = false;		//�Đ������ǂ���
		Vector3 m_footstepPos = g_vec3Zero;		//�t�b�g�X�e�b�v�{�[���̍��W
		Vector3 m_footstepDeltaValue = g_vec3Zero;		//�t�b�g�X�e�b�v�̈ړ��x�N�g��
		float m_interpolateEndTime = 1.0f;		//�⊮�I������
		float m_interpolateTime = 0.0f;		//���݂̕⊮����
	};
}