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
		//ファイルの読み込みに失敗した。
		if (m_tkaFile.IsLoaded() == false)
		{
			//処理を停止する
			std::abort();
		}
		
		BuildKeyFramesAndAnimationEvents();
	}
	
	void AnimationClip::BuildKeyFramesAndAnimationEvents()
	{
		//キーフレーム情報の構築
		//キーフレームの配列の容量を再確保
		m_keyframes.reserve(m_tkaFile.GetNumKeyFrame());
		//キーフレームにクエリを行う
		m_tkaFile.QueryKeyFrames([&](const TkaFile::KeyFrame& tkaKeyFrame) {
			//キーフレームのユニークポインタのオブジェクトを生成。
			auto keyframe = std::make_unique<KeyFrame>();
			//各情報を代入
			keyframe->boneIndex = tkaKeyFrame.boneIndex;
			keyframe->transform = Matrix::Identity;
			keyframe->time = tkaKeyFrame.time;
			for (auto j = 0; j < 4; j++)
			{
				keyframe->transform.m[j][0] = tkaKeyFrame.transform[j].x;
				keyframe->transform.m[j][1] = tkaKeyFrame.transform[j].y;
				keyframe->transform.m[j][2] = tkaKeyFrame.transform[j].z;
			}
			//keyframeをキャストして代入
			m_keyframes.push_back(std::move(keyframe));
		});
		//ボーンインデックスごとのキーフレームの連結リストを作成する
		//ボーンの最大数で容量を再確保
		m_keyFramePtrListArray.resize(MAX_BONE);
		for (auto& keyframe : m_keyframes)
		{
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
			//キーフレームの先頭のポインタが設定されていないとき
			if (m_topBoneKeyFrameList == nullptr)
			{
				//キーフレームの先頭のポインタを設定
				m_topBoneKeyFrameList = &m_keyFramePtrListArray[keyframe->boneIndex];
			}
		}
	}
}