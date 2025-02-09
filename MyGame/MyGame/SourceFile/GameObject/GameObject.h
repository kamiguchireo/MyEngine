#pragma once
#include "SourceFile/Noncopyable.h"

namespace Engine {
	typedef unsigned char	GameObjectPrio;

	class IGameObject:Engine::Noncopyable
	{
	public:
		IGameObject():
			m_priority(0),
			m_isDead(false),
			m_isNewFromGameObjectManager(false)
		{
		}
		virtual	~IGameObject()
		{
		}
	
	public:
		//イベント
		enum class EnEvent : int {
			enEvent_Undef,		//未定義イベント
			enEvent_Destroy		//インスタンスが破棄される
		};

		////イベント発生時のデータ
		//struct SEventParam {
		//	EnEvent eEvent = EnEvent::enEvent_Undef;		//発生しているイベント
		//	IGameObject*gameObject = nullptr;	//イベントを通知しているゲームオブジェクトのインスタンス
		//};
	public:

	//アップデート前描画
	virtual void PreRender() {}

	//初期化
	virtual bool Start() { return true; }

	//更新
	virtual void Update() {}
	
	//描画
	virtual void Draw() {}

	//オンデストロイ
	virtual void OnDestroy() {}

	//Render関数が実行された後で呼ばれる描画処理
	virtual void PostRender() {}
	public:
		void StartWrapper()
		{
			if (NextRenderStep == GameObjectStep::StartStep)
			{
				if (!is_StartEnd)
				{
					if (Start()) {
						is_StartEnd = true;
					}
				}
				//初期化処理完了。
				NextRenderStep = GameObjectStep::PreRenderStep;

			}
		}

		void PreRenderWrapper()
		{
			if (NextRenderStep == GameObjectStep::PreRenderStep)
			{
				if (!m_isDead)
				{
					PreRender();
				}
				NextRenderStep = GameObjectStep::UpdateStep;
			}
		}

		void UpdateWrapper()
		{
			if (NextRenderStep == GameObjectStep::UpdateStep)
			{
				if (!m_isDead)
				{
					Update();
				}
				NextRenderStep = GameObjectStep::DrawStep;
			}
		}

		void DrawWrapper()
		{
			if (NextRenderStep == GameObjectStep::DrawStep)
			{
				if (!m_isDead)
				{
					Draw();
				}
				NextRenderStep = GameObjectStep::PostRenderStep;
			}
		}

		void PostRenderWrapper()
		{
			if (NextRenderStep == GameObjectStep::PostRenderStep)
			{
				if (!m_isDead)
				{
					PostRender();
				}
				NextRenderStep = GameObjectStep::PreRenderStep;
			}
		}

		void OnDestoroyWrapper()
		{
			//SEventParam param;
			//param.eEvent = EnEvent::enEvent_Destroy;
			//param.gameObject = this;
			////デストロイイベントをリスナーに通知する。
			//for (auto&listener : m_eventListeners)
			//{
			//	listener(param);
			//}
			OnDestroy();
		}

		void SetDeadMark()
		{
			m_isDead = true;
		}
		//死亡判定。
		bool IsDead()const
		{
			return m_isDead;
		}

		GameObjectPrio GetPriority() const
		{
			return m_priority;
		}

		bool IsNewFromGameObjectManagr() const
		{
			return m_isNewFromGameObjectManager;
		}

		friend class CGameObjectManager;
	protected:
		GameObjectPrio	m_priority;			//!<実行優先度。
		unsigned int m_nameKey = 0;			//!<名前キー。
		bool m_isRegistDeadList = false;	//!<死亡リストに積まれている。
		bool m_isNewFromGameObjectManager;	//!<GameObjectManagerでnewされた
		bool m_isRegist = false;			//!<GameObjectManagerに登録されているかどうか
		bool m_isDead = false;						//!<死亡フラグ。
		bool m_isActive = true;				//Activeフラグ
		//std::list<std::function<void(SEventParam&eventParam)>> m_eventListeners;	//イベントリスナー
		bool is_StartEnd = false;

	private:
	enum class GameObjectStep : int{
		StartStep,
		PreRenderStep,
		UpdateStep,
		DrawStep,
		PostRenderStep
	};
	GameObjectStep NextRenderStep = GameObjectStep::StartStep;		//ゲームオブジェクトマネージャー内で使う次に実行する実行ステップ
	};
}