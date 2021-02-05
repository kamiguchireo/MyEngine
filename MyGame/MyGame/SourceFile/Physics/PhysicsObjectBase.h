#pragma once

namespace Engine {
	//物理オブジェクトのベースクラス
	class PhysicsObjectBase
	{
	public:
		//ゴーストオブジェクトを解放
		virtual void Release() = 0;

	private:
		//性的物理オブジェクト作成処理の共通処理
		virtual void CreateCommon(Vector3 pos, Quaternion rot) = 0;

	public:
		PhysicsObjectBase()
		{

		}
		~PhysicsObjectBase()
		{

		}

	protected:
		std::unique_ptr<ICollider> m_collider;		//コライダー
	};
}