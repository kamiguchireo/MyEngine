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

		//キーフレーム番号を進める
		ProgressKeyFrameNo(deltaTime);

		//ボーン行列をアニメーションクリップからサンプリングしていく
		SamplingBoneMatrixFromAnimationClip();

		//親の骨座標系になっているボーン行列をルートのボーンの空間に変換する
		CalcBoneMatrixInRootBoneSpace();

		//footstepのボーンの移動量を取得する
		SamplingDeltaValueFootStepBone();
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
				else
				{
					//ワンショット再生
					m_currentKeyFrameNo--;
					m_isPlaying = false;		//再生終わり
				}
				break;
			}
			if (topBoneKeyFrameList.at(m_currentKeyFrameNo)->time >= m_time)
			{
				//終わり
				break;
			}
			m_currentKeyFrameNo++;
		}
	}

	void AnimationPlayController::StartLoop()
	{
		m_footstepPos = g_vec3Zero;
		m_currentKeyFrameNo = 0;
		m_time = 0.0f;
	}

	void AnimationPlayController::SamplingBoneMatrixFromAnimationClip()
	{
		//キーフレームの配列を取得
		const auto& keyFramePtrListArray = m_animationClip->GetKeyFramePtrListArray();
		for (const auto& keyFrameList : keyFramePtrListArray)
		{
			if (keyFrameList.size() == 0)
			{
				continue;
			}
			//現在再生中のキーフレームをとってくる
			KeyFrame* keyframe = keyFrameList.at(m_currentKeyFrameNo);
			m_boneMatrix[keyframe->boneIndex] = keyframe->transform;
		}
	}

	void AnimationPlayController::CalcBoneMatrixInRootBoneSpace()
	{
		int numBone = m_skeleton->GetNumBones();
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			//ルートの骨を検索する
			auto bone = m_skeleton->GetBone(boneNo);
			//親のボーン番号を取得
			if (bone->GetParentBoneNo() != -1)
			{
				continue;
			}
			CalcBoneMatrixInRootBoneSpace(*bone, g_matIdentity);
		}
	}

	void AnimationPlayController::CalcBoneMatrixInRootBoneSpace(Bone& bone, Matrix parentMatrix)
	{
		//ワールド行列を計算する
		//現在再生中のボーン行列を取得
		auto& mBoneInRootSpace = m_boneMatrix[bone.GetNo()];
		Matrix localMatrix = m_boneMatrix[bone.GetNo()];

		//親の行列とローカル行列を乗算して、ワールド行列を計算する
		mBoneInRootSpace = localMatrix * parentMatrix;

		//子供のワールド行列も計算する
		for (auto& childBone : bone.GetChildren())
		{
			CalcBoneMatrixInRootBoneSpace(*childBone, mBoneInRootSpace);
		}
	}

	void AnimationPlayController::SamplingDeltaValueFootStepBone()
	{
		if (m_currentKeyFrameNoLastFrame == m_currentKeyFrameNo)
		{
			//キーフレームが進んでいない。
			return;
		}
		if (m_footstepBoneNo == -1)
		{
			return;
		}
		int numBone = m_skeleton->GetNumBones();
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			auto bone = m_skeleton->GetBone(boneNo);
			if (m_footstepBoneNo == bone->GetNo())
			{
				auto mat = m_boneMatrix[bone->GetNo()];
				Vector3 footstepBonePos;
				footstepBonePos.x = mat.m[3][0];
				footstepBonePos.x = mat.m[3][1];
				footstepBonePos.x = mat.m[3][2];
				//このフレームでのfootstepの移動量を計算する
				m_footstepDeltaValue = footstepBonePos - m_footstepPos;
				//このフレームでのfootstepの座標を更新する
				m_footstepPos = footstepBonePos;
				break;
			}
		}
	}
}