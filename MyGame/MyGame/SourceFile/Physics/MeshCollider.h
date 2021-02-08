#pragma once
#include "ICollider.h"
//#include "BulletCollision/CollisionDispatch/btCollisionWorldImporter.h"
//#include "BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h"

namespace Engine {
	class MeshCollider :public ICollider
	{
	public:
		MeshCollider();
		~MeshCollider();
		
		//tkmファイルからメッシュコライダーを生成
		//tkmFile		tkmファイル
		void CreateFromTkmFile(const TkmFile& tkmFile, const Matrix* offsetMatrix);
		//モデルからメッシュコライダーを生成
		//model		スキンモデル
		void CreateFromModel(const Model& model, const Matrix* offsetMatrix);

		btCollisionShape* GetBody() const override
		{
			return m_meshShape.get();
		}

	private:
		std::unique_ptr<btTriangleIndexVertexArray> m_stridingMeshInterface;
		typedef std::vector<Vector3> VertexBuffer;		//頂点バッファ。
		typedef std::unique_ptr<VertexBuffer> VertexBufferPtr;
		std::vector<VertexBufferPtr> m_vertexBufferArray;		//頂点バッファの配列。
		typedef std::vector<unsigned int> IndexBuffer;		//インデックスバッファ。
		typedef std::unique_ptr<IndexBuffer> IndexBufferPtr;
		std::vector<IndexBufferPtr> m_indexBufferArray;		//インデックスバッファの配列。
		std::unique_ptr<btBvhTriangleMeshShape> m_meshShape;		//メッシュ形状
	};
}