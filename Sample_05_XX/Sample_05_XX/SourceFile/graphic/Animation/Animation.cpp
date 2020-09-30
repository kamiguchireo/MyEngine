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
		//最後のポーズだけ進める
		int lastIndex = GetLastAnimationControllerIndex();
		m_animationPlayController[lastIndex].Update(deltaTime, this);

	}

	void Animation::UpdateGlobalPose()
	{
		//グローバルポーズ計算用のメモリを確保
		int numBone = m_skeleton->GetNumBones();
		Quaternion* qGlobalPose = (Quaternion*)alloca(sizeof(Quaternion) * numBone);
		Vector3* vGlobalPose = (Vector3*)alloca(sizeof(Vector3) * numBone);
		Vector3* vGlobalScale = (Vector3*)alloca(sizeof(Vector3) * numBone);
		//footstepの移動量を初期化
		m_footstepDeltaValue = g_vec3Zero;
		for (int i = 0; i < numBone; i++)
		{
			qGlobalPose[i] = Quaternion::Identity;
			vGlobalPose[i] = Vector3::Zero;
			vGlobalScale[i] = Vector3::One;
		}
		//グローバルポーズを計算
		int startIndex = m_startAnimationPlayController;
		for (int i = 0; i < m_numAnimationPlayController; i++)
		{
			int index = GetAnimationControllerIndecx(startIndex, i);
			float interpolateRate = m_animationPlayController[index].GetInterpolateRate();
			const auto& localBoneMatrix = m_animationPlayController[index].GetBoneLocalMatrix();
			auto deltaValueFootStep = m_animationPlayController[index].GetFootStepDeltaValueOnUpdate();
			//footstepの移動量の補完
			m_footstepDeltaValue.Lerp(interpolateRate, m_footstepDeltaValue, deltaValueFootStep);
			for (int boneNo = 0; boneNo < numBone; boneNo++)
			{
				//平行移動の補完
				Matrix m = localBoneMatrix[boneNo];
				vGlobalPose[boneNo].Lerp(interpolateRate, vGlobalPose[boneNo], *(Vector3*)m.m[3]);
				//平行移動成分を削除
				m.m[3][0] = 0.0f;
				m.m[3][1] = 0.0f;
				m.m[3][2] = 0.0f;

				//拡大成分の補完
				Vector3 vBoneScale;
				vBoneScale.x = (*(Vector3*)m.m[0]).Length();
				vBoneScale.x = (*(Vector3*)m.m[1]).Length();
				vBoneScale.x = (*(Vector3*)m.m[2]).Length();

				vGlobalScale[boneNo].Lerp(interpolateRate, vGlobalScale[boneNo], vBoneScale);
				//拡大成分を除去
				m.m[0][0] /= vBoneScale.x;
				m.m[0][1] /= vBoneScale.x;
				m.m[0][2] /= vBoneScale.x;

				m.m[1][0] /= vBoneScale.y;
				m.m[1][1] /= vBoneScale.y;
				m.m[1][2] /= vBoneScale.y;

				m.m[2][0] /= vBoneScale.z;
				m.m[2][1] /= vBoneScale.z;
				m.m[2][2] /= vBoneScale.z;

				//回転の補完
				Quaternion qBone;
				qBone.SetRotation(m);
				qGlobalPose[boneNo].Slerp(interpolateRate, qGlobalPose[boneNo], qBone);
			}
		}
		//グローバルポーズをスケルトンに反映させる
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			//拡大行列を作成
			Matrix scaleMatrix;
			scaleMatrix.MakeScaling(vGlobalScale[boneNo]);
			//回転行列を作成
			Matrix rotMatrix;
			rotMatrix.MakeRotationFromQuaternion(qGlobalPose[boneNo]);
			//平行移動行列を作成
			Matrix transMat;
			transMat.MakeTranslation(vGlobalPose[boneNo]);

			//全部を合成して、ボーン行列を作成
			Matrix boneMatrix;
			boneMatrix = scaleMatrix * rotMatrix;
			boneMatrix = boneMatrix * transMat;

			m_skeleton->SetBoneLocalMatrix(
				boneNo,
				boneMatrix
			);
		}
		//最終アニメーション以外は補完完了していたら除去する
		int numAnimationPlayController = m_numAnimationPlayController;
		for (int i = 1; i < m_numAnimationPlayController; i++)
		{
			int index = GetAnimationControllerIndecx(startIndex, i);
			if (m_animationPlayController[index].GetInterpolateRate() > 0.99999f)
			{
				//補完が終わっているのでアニメーションの開始位置を前にする
				m_startAnimationPlayController = index;
				numAnimationPlayController = m_numAnimationPlayController - i;
			}
		}
		m_numAnimationPlayController = numAnimationPlayController;
	}

	void Animation::Progress(float deltaTime)
	{
		if (m_numAnimationPlayController == 0)
		{
			//アニメーションプレイコントローラの数が不正です
			std::abort();
		}
		m_deltaTimeOnUpdate = deltaTime;
		//ローカルポーズの更新
		UpdateLocalPose(deltaTime);

		//グローバルポーズを計算
		UpdateGlobalPose();
	}
}