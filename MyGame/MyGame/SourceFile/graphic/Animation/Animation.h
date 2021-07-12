#pragma once
#include "SourceFile/graphic/Animation/AnimationClip.h"
#include "SourceFile/graphic/Animation/AnimationPlayController.h"

class Skeleton;

namespace Engine {
	class Animation
	{
	public:
		Animation()
		{
		}
		~Animation()
		{
		}

		//初期化処理
		//skeleton		スケルトン
		//animClips		アニメーションクリップ
		//numAnimClip	アニメーションクリップの数
		void Init(Skeleton& skeleton,AnimationClip animClips[],int numAnimClip);

		//アニメーションの再生
		//clipNo		アニメーションクリップの番号
		//interpolateTime		補完時間
		void Play(int clipNo, float interpolateTime = 0.0f)
		{
			if (clipNo < m_animationClips.size())
			{
				PlayCommon(m_animationClips[clipNo], interpolateTime);
			}
		}

		//アニメーションを進める
		//エンジン内部で使用します
		//deltaTime		アニメーションを進める時間(単位：秒)
		//戻り値はfootstepの移動量
		Vector3 Update(float deltaTime);

		bool IsPlaying()
		{
			int lastPoseIndex = GetLastAnimationControllerIndex();
			return m_animationPlayController[lastPoseIndex].IsPlaying();
		}
	private:
		////////////////////////////////////
		////////アニメーション再生系////////
		////////////////////////////////////

		//アニメーションの再生
		void PlayCommon(AnimationClip* nextClip, float interpolateTime);


		//ローカルポーズの更新
		//deltaTime		アニメーションを進める時間(単位：秒)
		void UpdateLocalPose(float deltaTime);

		//グローバルポーズの更新
		//戻り値はfootstepの移動量
		Vector3 UpdateGlobalPose();
	private:
		////////////////////////////////////////////////////
		////アニメーションコントローラのインデックス取得////
		////////////////////////////////////////////////////

		//アニメーションコントローラのリングバッファ上でのインデックスを取得
		//startIndex		開始インデックス
		//localIndex		ローカルインデックス
		int GetAnimationControllerIndecx(int startIndex, int localIndex)const
		{
			return (startIndex + localIndex) % ANIMATION_PLAY_CONTROLLER_NUM;
		}
		//最終ポーズになるアニメーションのリングバッファ上でのインデックスを取得
		int GetLastAnimationControllerIndex()const
		{
			return GetAnimationControllerIndecx(m_startAnimationPlayController, m_numAnimationPlayController - 1);
		}
	private:
		static const int ANIMATION_PLAY_CONTROLLER_NUM = 32;	//!<アニメーションコントローラの数。
		Skeleton* m_skeleton = nullptr;		//アニメーションを適用するスケルトン
		std::vector<AnimationClip*> m_animationClips;		//アニメーションクリップの配列
		AnimationPlayController m_animationPlayController[ANIMATION_PLAY_CONTROLLER_NUM];		//アニメーションプレイコントローラ
		int m_startAnimationPlayController = 0;		//アニメーションコントローラの開始インデックス
		int m_numAnimationPlayController = 0;		//現在使用中のアニメーション再生コントローラの数
		float m_interpolateTime = 0.0f;		//現在の補完時間
		float m_interpolateTimeEnd = 0.0f;		//補完終了時間
		bool m_isInited = false;
		int m_footStepBoneNo = -1;		//footstepのボーン番号
	};
}