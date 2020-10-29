#pragma once
//アニメーションの再生コントローラ
class Skeleton;


namespace Engine {
	class AnimationClip;
	class Animation;

	//アニメーションの再生コントローラ
	//一つのアニメーションクリップに対してアニメーションを進めて、
	//ローカルポーズを計算する
	class AnimationPlayController
	{
	public:
		AnimationPlayController()
		{
		}
		~AnimationPlayController()
		{
		}

		//初期化
		//skeleton		スケルトン
		//footStepBoneNo	footStepのボーン番号	
		void Init(Skeleton* skeleton, int footStepBoneNo);

		//アニメーションクリップの取得
		AnimationClip* GetAnimClip()const
		{
			return m_animationClip;
		}

		//アニメーションクリップの変更
		void ChangeAnimationClip(AnimationClip* clip)
		{
			m_animationClip = clip;
			m_currentKeyFrameNo = 0;
			m_time = 0.0f;
			m_isPlaying = true;		//再生中
			m_footstepPos = g_vec3Zero;		//フットステップの位置
			m_footstepDeltaValue = g_vec3Zero;		//フットステップの移動ベクトル
		}

		//アニメーションクリップの補完時間の設定
		void SetInterpolateTime(float interpolateTime)
		{
			if (interpolateTime < 0.0f)
			{
				//補完時間が不正です
				std::abort();
			}
			//補完の終わる時間を設定
			m_interpolateEndTime = interpolateTime;
			//現在の補完時間を設定
			m_interpolateTime = 0.0f;			
		}
		//更新処理
		//deltaTime		アニメーションを進める時間
		//animation		アニメーション
		void Update(float deltaTime/*, Animation* animation*/);

		//キーフレーム番号を進める
		void ProgressKeyFrameNo(float deltaTime);

		//ループ再生開始するときの処理
		void StartLoop();

		//ボーン行列をアニメーションクリップからサンプリングする
		void SamplingBoneMatrixFromAnimationClip();

		//ルートボーン空間での行列を計算する
		void CalcBoneMatrixInRootBoneSpace();
		//bone		計算するボーン
		//parentMatrix		親の行列
		void CalcBoneMatrixInRootBoneSpace(Bone&bone,Matrix parentMatrix);

		//footstepのボーンの変化量をサンプリングする
		void SamplingDeltaValueFootStepBone();

		//footstepボーンの座標を全体の骨から減算する
		void SubtractFootstepBonePosFromAllBone();

		//補完率を取得
		float GetInterpolateRate()const
		{
			if (m_interpolateEndTime <= 0.0f)
			{
				return 1.0f;
			}
			return min(1.0f, m_interpolateTime / m_interpolateEndTime);
		}

		//ローカルボーン行列を取得
		const std::vector<Matrix>& GetBoneLocalMatrix()const
		{
			return m_boneMatrix;
		}

		//Update関数を呼び出した時の、footstepボーンの移動量を取得
		Vector3 GetFootStepDeltaValueOnUpdate()const
		{
			return m_footstepDeltaValue;
		}
	private:
		int m_footstepBoneNo = -1;		//フットステップのボーンの番号
		std::vector<Matrix> m_boneMatrix;		//このコントローラで再生中のアニメーションのボーン行列
		Skeleton* m_skeleton = nullptr;				//スケルトン。
		AnimationClip* m_animationClip = nullptr;		//アニメーションクリップ
		int m_currentKeyFrameNoLastFrame = 0;		//1フレーム前のキーフレーム番号。
		int m_currentKeyFrameNo = 0;		//現在再生中のキーフレーム番号
		float m_time = 0.0f;
		bool m_isPlaying = false;		//再生中かどうか
		Vector3 m_footstepPos = g_vec3Zero;		//フットステップボーンの座標
		Vector3 m_footstepDeltaValue = g_vec3Zero;		//フットステップの移動ベクトル
		float m_interpolateEndTime = 1.0f;		//補完終了時間
		float m_interpolateTime = 0.0f;		//現在の補完時間
	};
}