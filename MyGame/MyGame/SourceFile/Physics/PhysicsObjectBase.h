#pragma once
#include "SourceFile/graphic/ModelRender.h"

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

		//メッシュ形状のゴーストオブジェクトを作成
		//pos		座標
		//rot		回転
		//skinModel	モデル
		void CreateMesh(Vector3 pos, Quaternion rot, const Model& skinModel);
	protected:
		std::unique_ptr<ICollider> m_collider;		//コライダー
	};
}