#pragma once
#include "tkFile/tkaFile.h"

namespace Engine {

	//キーフレーム
	struct KeyFrame {
		uint32_t boneIndex;		//ボーンインデックス
		float time;		//時間
		Matrix transform;		//トランスフォーム
	};

	class AnimationClip :public Noncopyable
	{
	public:
		using KeyFramePtrList = std::vector<KeyFrame*>;		//キーフレームのポインタの配列を別名定義
		AnimationClip();
		~AnimationClip();

		//読み込み処理
		void Load(const char* filePath);

		//キーフレームとアニメーションイベントを構築する
		//ロードが終わった時に呼び出してください
		void BuildKeyFramesAndAnimationEvents();

		//ロード済みかの判定
		bool IsLoaded()const
		{
			return m_tkaFile.IsLoaded();
		}

		//先頭のキーフレームのポインタを取得
		const KeyFramePtrList& GetTopBoneKeyFrameList()const
		{
			return *m_topBoneKeyFrameList;
		}

		//ループするか
		bool IsLoop()const
		{
			return m_isLoop;
		}

		//ループフラグを設定する
		void SetLoopFlag(bool flag)
		{
			m_isLoop = flag;
		}
	private:
		using KeyFramePtr = std::unique_ptr<KeyFrame>;		//キーフレームのポインタを別名定義
		TkaFile m_tkaFile;		//tksファイル
		std::vector<KeyFramePtr> m_keyframes;		//キーフレーム
		std::vector<KeyFramePtrList> m_keyFramePtrListArray;		//ボーンごとのキーフレームのリストを管理するための二次元配列
		KeyFramePtrList* m_topBoneKeyFrameList = nullptr;		//先頭のキーフレームのポインタ
		bool m_isLoop = false;		//ループフラグ
	};
}