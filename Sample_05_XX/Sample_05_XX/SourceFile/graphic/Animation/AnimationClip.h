#pragma once
#include "tkFile/tkaFile.h"

namespace Engine {

	//�L�[�t���[��
	struct KeyFrame {
		uint32_t boneIndex;		//�{�[���C���f�b�N�X
		float time;		//����
		Matrix transform;		//�g�����X�t�H�[��
	};

	class AnimationClip :public Noncopyable
	{
	public:
		using KeyFramePtrList = std::vector<KeyFrame*>;		//�L�[�t���[���̃|�C���^�̔z���ʖ���`
		AnimationClip();
		~AnimationClip();

		//�ǂݍ��ݏ���
		void Load(const char* filePath);

		//�L�[�t���[���ƃA�j���[�V�����C�x���g���\�z����
		//���[�h���I��������ɌĂяo���Ă�������
		void BuildKeyFramesAndAnimationEvents();

		//���[�h�ς݂��̔���
		bool IsLoaded()const
		{
			return m_tkaFile.IsLoaded();
		}

		//�擪�̃L�[�t���[���̃|�C���^���擾
		const KeyFramePtrList& GetTopBoneKeyFrameList()const
		{
			return *m_topBoneKeyFrameList;
		}

		//���[�v���邩
		bool IsLoop()const
		{
			return m_isLoop;
		}

		//���[�v�t���O��ݒ肷��
		void SetLoopFlag(bool flag)
		{
			m_isLoop = flag;
		}
	private:
		using KeyFramePtr = std::unique_ptr<KeyFrame>;		//�L�[�t���[���̃|�C���^��ʖ���`
		TkaFile m_tkaFile;		//tks�t�@�C��
		std::vector<KeyFramePtr> m_keyframes;		//�L�[�t���[��
		std::vector<KeyFramePtrList> m_keyFramePtrListArray;		//�{�[�����Ƃ̃L�[�t���[���̃��X�g���Ǘ����邽�߂̓񎟌��z��
		KeyFramePtrList* m_topBoneKeyFrameList = nullptr;		//�擪�̃L�[�t���[���̃|�C���^
		bool m_isLoop = false;		//���[�v�t���O
	};
}