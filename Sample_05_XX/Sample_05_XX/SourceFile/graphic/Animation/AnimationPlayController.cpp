#include "stdafx.h"
#include "AnimationPlayController.h"

namespace Engine {
	//初期化処理
	void AnimationPlayController::Init(Skeleton* skeleton, int footStepBoneNo)
	{
		m_footstepBoneNo = footStepBoneNo;
		int numBones = skeleton->GetNumBones();
		//ボーン行列を確保
		m_boneMatrix.resize(numBones);
		m_skeleton = skeleton;
	}

	void AnimationPlayController::Update(float deltaTime, Animation* animation)
	{
		if (m_animationClip == nullptr)
		{
			//アニメーションクリップがありません
			std::abort();
		}

		m_time += deltaTime;
	}

	void AnimationPlayController::ProgressKeyFrameNo(float deltaTime)
	{
		//1フレーム前のキーフレーム番号を記録しておく
		m_currentKeyFrameNoLastFrame = m_currentKeyFrameNo;

		const auto& topBoneKeyFrameList = m_animationClip->GetTopBoneKeyFrameList();

		//補完時間も進めていく
		m_interpolateTime = min(1.0f, m_interpolateTime + deltaTime);
		while (true)
		{
			//キーフレームが終端まで行ったとき
			if (m_currentKeyFrameNo >= (int)topBoneKeyFrameList.size())
			{
				//ループするか?
				if (m_animationClip->IsLoop())
				{
					//ループ
					StartLoop();
				}
			}
		}
	}

	void AnimationPlayController::StartLoop()
	{
		m_footstepPos = g_vec3Zero;
		m_currentKeyFrameNo = 0;
		m_time = 0.0f;
	}
}