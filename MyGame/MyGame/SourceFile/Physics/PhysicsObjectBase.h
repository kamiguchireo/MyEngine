#pragma once
#include "SourceFile/graphic/ModelRender.h"
#include "ICollider.h"

namespace Engine {
	//物理オブジェクトのベースクラス
	class PhysicsObjectBase
	{
	public:
		//ゴーストオブジェクトを解放
		virtual void Release() = 0;

	private:
		//静的物理オブジェクト作成処理の共通処理
		virtual void CreateCommon(Vector3 pos, Quaternion rot) = 0;

	public:
		PhysicsObjectBase()
		{

		}
		~PhysicsObjectBase()
		{

		}

		//ボックス形状のゴーストオブジェクトを作成
		//pos		座標
		//rot		回転
		//size		サイズ
		void CreateBox(Vector3 pos, Quaternion rot, Vector3 size);

		//カプセル形状のゴーストオブジェクトを作成
		// pos		座標
		// rot		回転
		// radius		カプセルの半径
		// height		カプセルの高さ
		void CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height);

		//球体形状のゴーストオブジェクトを作成
		//pos		座標
		//rot		回転
		//radius		球体の半径
		void CreateSphere(Vector3 pos, Quaternion rot, float radius);

		//円柱形状のゴーストオブジェクトを作成
		//pos		座標
		//rot		回転
		//size		円柱のサイズ
		void CreateCylinder(Vector3 pos, Quaternion rot, Vector3 size);
		//メッシュ形状のゴーストオブジェクトを作成
		//pos		座標
		//rot		回転
		//skinModel	モデル
		void CreateMesh(Vector3 pos, Quaternion rot, const Model& skinModel);
	protected:
		std::unique_ptr<ICollider> m_collider;		//コライダー
	};
}