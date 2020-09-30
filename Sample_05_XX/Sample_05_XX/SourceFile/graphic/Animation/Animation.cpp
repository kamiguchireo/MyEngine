#include "stdafx.h"
#include "Animation.h"

namespace Engine
{
	void Animation::Init(Skeleton& skeleton, const std::vector<std::unique_ptr<AnimationClip>>&animClips)
	{
		//アニメーションクリップがからの時
		if (animClips.empty() == true)
		{
			//アニメーションクリップがからです
			std::abort();
		}
		m_skeleton = &skeleton;

		//アニメーションクリップの数だけ回す
		for (auto& animClip : animClips)
		{
			m_animationClips.push_back(animClip.get());
		}

		//footStepボーンの番号を調べる
		int footsteoBoneNo = -1;
		int numBone = m_skeleton->GetNumBones();
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			auto bone = m_skeleton->GetBone(boneNo);
			//footstepで名前検索
			if (wcscmp(bone->GetName(), L"footstep") == 0)
			{
				//footstepボーンがみつかった
				footsteoBoneNo = boneNo;
				break;
			}
		}

		for (auto& ctr : m_animationPlayController)
		{
			ctr.Init(m_skeleton, footsteoBoneNo);
		}
	}

	//アニメーションの再生
	void Animation::PlayCommon(AnimationClip*nextClip,float interpolateTime)
	{
		if (nextClip->IsLoaded() == false)
		{
			//アニメーションクリップがロードされていません。
			std::abort();
		}
		//最終ポーズとなるアニメーションクリップのインデックスを取得
		int index = GetLastAnimationControllerIndex();
		//アニメーションクリップが1つの時補完せずに終了
		if (m_animationPlayController[index].GetAnimClip() == nextClip)
		{
			return;
		}
		if (interpolateTime == 0.0f)
		{
			//補完なし
			m_numAnimationPlayController = 1;
		}
		else 
		{
			//補完あり
			m_numAnimationPlayController++;
		}
		index = GetLastAnimationControllerIndex();
		//アニメーションクリップの切り替え
		m_animationPlayController[index].ChangeAnimationClip(nextClip);
		m_animationPlayController[index].SetInterpolateTime(interpolateTime);
		m_interpolateTime = 0.0f;
		m_interpolateTimeEnd = interpolateTime;
	}

	//ローカルポーズの更新
	void Animation::UpdateLocalPose(float deltaTime)
	{
		//補完時間を進めていく
		m_interpolateTime += deltaTime;
		if (m_interpolateTime >= 1.0f)
		{
			//補完完了
			//現在の最終アニメーションコントローラへのインデックスが開始インデックスになる
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
			//アニメーションプレイコントローラの数が不正です
			std::abort();
		}
		m_deltaTimeOnUpdate = deltaTime;
	}
}