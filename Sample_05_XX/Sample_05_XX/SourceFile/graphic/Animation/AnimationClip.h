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
	private:
		using KeyFramePtr = std::unique_ptr<KeyFrame>;		//�L�[�t���[���̃|�C���^��ʖ���`
		TkaFile m_tkaFile;		//tks�t�@�C��
		std::vector<KeyFramePtr> m_keyframes;		//�L�[�t���[��
		std::vector<KeyFramePtrList> m_keyFramePtrListArray;		//�{�[�����Ƃ̃L�[�t���[���̃��X�g���Ǘ����邽�߂̓񎟌��z��
		KeyFramePtrList* m_topBoneKeyFrameList = nullptr;		//�擪�̃L�[�t���[���̃|�C���^
	};
}