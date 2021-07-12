#include "stdafx.h"
#include "Animation.h"

namespace Engine
{
	void Animation::Init(Skeleton& skeleton,AnimationClip animClips[],int numAnimClip)
	{
		//アニメーションクリップがからの時
		if (animClips == nullptr)
		{
			//アニメーションクリップがからです
			std::abort();
		}
		m_skeleton = &skeleton;

		//アニメーションクリップの数だけ回す
		for (int i = 0; i < numAnimClip; i++)
		{
			m_animationClips.push_back(&animClips[i]);
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
		Play(0);
		m_isInited = true;
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
			m_animationPlayController[index].Update(deltaTime/*, this*/);
		}
		//最後のポーズだけ進める
		int lastIndex = GetLastAnimationControllerIndex();
		m_animationPlayController[lastIndex].Update(deltaTime/*, this*/);

	}

	Vector3 Animation::UpdateGlobalPose()
	{
		//グローバルポーズ計算用のメモリを確保
		int numBone = m_skeleton->GetNumBones();
		Quaternion* qGlobalPose = (Quaternion*)_malloca(sizeof(Quaternion) * numBone);
		Vector3* vGlobalPose = (Vector3*)_malloca(sizeof(Vector3) * numBone);
		Vector3* vGlobalScale = (Vector3*)_malloca(sizeof(Vector3) * numBone);
		for (int i = 0; i < numBone; i++)
		{
			//NULLチェック
			if (qGlobalPose)
			{
				qGlobalPose[i] = Quaternion::Identity;
			}
			//NULLチェック
			if (vGlobalPose)
			{
				vGlobalPose[i] = Vector3::Zero;
			}
			//NULLチェック
			if (vGlobalScale)
			{
				vGlobalScale[i] = Vector3::One;
			}
		}
		//グローバルポーズを計算
		int startIndex = m_startAnimationPlayController;
		//アニメーション再生コントローラーの数分回す
		for (int i = 0; i < m_numAnimationPlayController; i++)
		{
			int index = GetAnimationControllerIndecx(startIndex, i);
			float interpolateRate = m_animationPlayController[index].GetInterpolateRate();
			const auto& localBoneMatrix = m_animationPlayController[index].GetBoneLocalMatrix();
			for (int boneNo = 0; boneNo < numBone; boneNo++)
			{
				//平行移動の補完
				Matrix m = localBoneMatrix[boneNo];
				//NULLチェック
				if (vGlobalPose)
				{
					vGlobalPose[boneNo].Lerp(interpolateRate, vGlobalPose[boneNo], *(Vector3*)m.m[3]);
				}
				//平行移動成分を削除
				m.m[3][0] = 0.0f;
				m.m[3][1] = 0.0f;
				m.m[3][2] = 0.0f;

				//拡大成分の補完
				Vector3 vBoneScale;
				vBoneScale.x = (*(Vector3*)m.m[0]).Length();
				vBoneScale.y = (*(Vector3*)m.m[1]).Length();
				vBoneScale.z = (*(Vector3*)m.m[2]).Length();

				//NULLチェック
				if (vGlobalScale)
				{
					vGlobalScale[boneNo].Lerp(interpolateRate, vGlobalScale[boneNo], vBoneScale);
				}
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
				Quaternion qBone = Quaternion::Identity;
				qBone.SetRotation(m);
				//NULLチェック
				if (qGlobalPose)
				{
					qGlobalPose[boneNo].Slerp(interpolateRate, qGlobalPose[boneNo], qBone);
				}

			}
		}
		//グローバルポーズをスケルトンに反映させる
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			//拡大行列を作成
			Matrix scaleMatrix;
			//NULLチェック
			if (vGlobalScale)
			{
				scaleMatrix.MakeScaling(vGlobalScale[boneNo]);
			}
			//回転行列を作成
			Matrix rotMatrix;
			//NULLチェック
			if (qGlobalPose)
			{
				rotMatrix.MakeRotationFromQuaternion(qGlobalPose[boneNo]);
			}
			//平行移動行列を作成
			Matrix transMat;
			//NULLチェック
			if (vGlobalPose)
			{
				transMat.MakeTranslation(vGlobalPose[boneNo]);
			}
			//全部を合成して、ボーン行列を作成
			Matrix boneMatrix;
			boneMatrix = scaleMatrix * rotMatrix;
			boneMatrix = boneMatrix * transMat;

			m_skeleton->SetBoneLocalMatrix(
				boneNo,
				boneMatrix
			);

			m_skeleton->GetBone(boneNo)->CalcWorldTRS(vGlobalPose[boneNo], qGlobalPose[boneNo], vGlobalScale[boneNo]);
			
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
		int lastAnimClip = GetLastAnimationControllerIndex();
		auto m_footstepDeltaValue = m_animationPlayController[lastAnimClip].GetFootStepDeltaValueOnUpdate();
		//footstepの移動量の補完
		//m_footstepDeltaValue.Lerp(interpolateRate, m_footstepDeltaValue, deltaValueFootStep);

		return m_footstepDeltaValue;
	}

	Vector3 Animation::Update(float deltaTime)
	{
		if (m_numAnimationPlayController == 0)
		{
			//アニメーションプレイコントローラの数が不正です
			std::abort();
		}
		//ローカルポーズの更新
		UpdateLocalPose(deltaTime);

		//グローバルポーズを計算
		return UpdateGlobalPose();
	}
}