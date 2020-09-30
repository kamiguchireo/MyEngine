#pragma once
//�A�j���[�V�����̍Đ��R���g���[��
class Skeleton;

namespace Engine {

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

	private:
		int						m_footstepBoneNo = -1;		//�t�b�g�X�e�b�v�̃{�[���̔ԍ�
		std::vector<Matrix> m_boneMatrix;		//���̃R���g���[���ōĐ����̃A�j���[�V�����̃{�[���s��
		Skeleton* m_skeleton = nullptr;				//�X�P���g���B

	};
}