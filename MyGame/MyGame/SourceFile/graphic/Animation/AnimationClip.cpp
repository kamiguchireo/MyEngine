#include "stdafx.h"
#include "AnimationClip.h"

namespace Engine {
	AnimationClip::AnimationClip()
	{

	}

	AnimationClip::~AnimationClip()
	{

	}

	void AnimationClip::Load(const char*filePath)
	{
		m_tkaFile.Load(filePath);
		//�t�@�C���̓ǂݍ��݂Ɏ��s�����B
		if (m_tkaFile.IsLoaded() == false)
		{
			//�������~����
			std::abort();
		}
		
		BuildKeyFramesAndAnimationEvents();
	}
	
	void AnimationClip::BuildKeyFramesAndAnimationEvents()
	{
		//�L�[�t���[�����̍\�z
		//�L�[�t���[���̔z��̗e�ʂ��Ċm��
		m_keyframes.reserve(m_tkaFile.GetNumKeyFrame());
		//�L�[�t���[���ɃN�G�����s��
		m_tkaFile.QueryKeyFrames([&](const TkaFile::KeyFrame& tkaKeyFrame) {
			//�L�[�t���[���̃��j�[�N�|�C���^�̃I�u�W�F�N�g�𐶐��B
			auto keyframe = std::make_unique<KeyFrame>();
			//�e������
			keyframe->boneIndex = tkaKeyFrame.boneIndex;
			keyframe->transform = Matrix::Identity;
			keyframe->time = tkaKeyFrame.time;
			for (auto j = 0; j < 4; j++)
			{
				keyframe->transform.m[j][0] = tkaKeyFrame.transform[j].x;
				keyframe->transform.m[j][1] = tkaKeyFrame.transform[j].y;
				keyframe->transform.m[j][2] = tkaKeyFrame.transform[j].z;
			}
			//keyframe���L���X�g���đ��
			m_keyframes.push_back(std::move(keyframe));
		});
		//�{�[���C���f�b�N�X���Ƃ̃L�[�t���[���̘A�����X�g���쐬����
		//�{�[���̍ő吔�ŗe�ʂ��Ċm��
		m_keyFramePtrListArray.resize(MAX_BONE);
		for (auto& keyframe : m_keyframes)
		{
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
			//�L�[�t���[���̐擪�̃|�C���^���ݒ肳��Ă��Ȃ��Ƃ�
			if (m_topBoneKeyFrameList == nullptr)
			{
				//�L�[�t���[���̐擪�̃|�C���^��ݒ�
				m_topBoneKeyFrameList = &m_keyFramePtrListArray[keyframe->boneIndex];
			}
		}
	}
}