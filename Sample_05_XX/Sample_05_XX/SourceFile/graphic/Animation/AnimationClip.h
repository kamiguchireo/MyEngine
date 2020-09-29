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
	private:
		using KeyFramePtr = std::unique_ptr<KeyFrame>;		//キーフレームのポインタを別名定義
		TkaFile m_tkaFile;		//tksファイル
		std::vector<KeyFramePtr> m_keyframes;		//キーフレーム
		std::vector<KeyFramePtrList> m_keyFramePtrListArray;		//ボーンごとのキーフレームのリストを管理するための二次元配列
		KeyFramePtrList* m_topBoneKeyFrameList = nullptr;		//先頭のキーフレームのポインタ
	};
}