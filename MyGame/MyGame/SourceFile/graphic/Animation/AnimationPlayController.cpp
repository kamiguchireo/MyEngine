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

	void AnimationPlayController::Update(float deltaTime/*, Animation* animation*/)
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

		//footstepのボーンの移動量を取得する
		SamplingDeltaValueFootStepBone();

		//アニメーション再生したフラグをスケルトンに立てる
		m_skeleton->SetMarkPlayAnimation();
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
		m_currentKeyFrameNo = 0;
		m_time = 0.0f;
		//ループするのでひとつ前のフレームのフットステップの移動量をリセット
		m_footstepLastValue = g_vec3Zero;
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
			if (keyframe->boneIndex < m_boneMatrix.size())
			{
				m_boneMatrix[keyframe->boneIndex] = keyframe->transform;
			}
			else
			{
				std::abort();
			}
		}
	}

	void AnimationPlayController::SamplingDeltaValueFootStepBone()
	{
		if (m_footstepBoneNo == -1)
		{
			return;
		}
		//ボーンの数分回す
		for (int boneNo = 0; boneNo < m_skeleton->GetNumBones(); boneNo++)
		{
			auto bone = m_skeleton->GetBone(boneNo);
			if (bone->GetParentBoneNo() == -1)
			{
				//ルートボーンの時
				Matrix footStepBoneWorldMatrix = Matrix::Identity;
				CalcFootStepBoneWorldMatrix(*bone, Matrix::Identity, footStepBoneWorldMatrix);
				m_footstepDeltaValue = Vector3::Zero;
				//フットステップを代入
				m_footstepDeltaValue.x = footStepBoneWorldMatrix.m[3][0];
				m_footstepDeltaValue.y = footStepBoneWorldMatrix.m[3][1];
				m_footstepDeltaValue.z = footStepBoneWorldMatrix.m[3][2];
				//フットステップの移動量を減算
				m_boneMatrix[bone->GetNo()].m[3][0] -= footStepBoneWorldMatrix.m[3][0];
				m_boneMatrix[bone->GetNo()].m[3][1] -= footStepBoneWorldMatrix.m[3][1];
				m_boneMatrix[bone->GetNo()].m[3][2] -= footStepBoneWorldMatrix.m[3][2];
				//このフレームでの異動量を知るためにひとつ前の移動量を減算
				m_footstepDeltaValue -= m_footstepLastValue;
				//次のフレームで使用する移動量を代入
				m_footstepLastValue.x = footStepBoneWorldMatrix.m[3][0];
				m_footstepLastValue.y = footStepBoneWorldMatrix.m[3][1];
				m_footstepLastValue.z = footStepBoneWorldMatrix.m[3][2];

				break;
			}
		}
	}

	void AnimationPlayController::CalcFootStepBoneWorldMatrix(Bone& bone, const Matrix& parentMatrix, Matrix& footStepBoneMatrix)
	{
		Matrix boneWorld = Matrix::Identity;
		Matrix localMatrix = m_boneMatrix[bone.GetNo()];
		boneWorld = localMatrix * parentMatrix;
		if (bone.GetNo() == m_footstepBoneNo)
		{
			//フットステップボーンがみつかった時
			footStepBoneMatrix = boneWorld;
			return;
		}
		//フットステップボーンがみつかるまで子供のボーンに適応する
		for (auto childBone : bone.GetChildren())
		{
			CalcFootStepBoneWorldMatrix(*childBone, boneWorld, footStepBoneMatrix);
		}
	}
}