#pragma once
//アニメーションの再生コントローラ
class Skeleton;

namespace Engine {

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

	private:
		int						m_footstepBoneNo = -1;		//フットステップのボーンの番号
		std::vector<Matrix> m_boneMatrix;		//このコントローラで再生中のアニメーションのボーン行列
		Skeleton* m_skeleton = nullptr;				//スケルトン。

	};
}