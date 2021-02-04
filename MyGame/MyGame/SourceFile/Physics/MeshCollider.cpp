#include "stdafx.h"
#include "MeshCollider.h"

namespace Engine {
	MeshCollider::MeshCollider()
	{

	}

	MeshCollider::~MeshCollider()
	{

	}

	//tkmファイルからメッシュコライダーを生成
	void MeshCollider::CreateFromTkmFile(const TkmFile& tkmFile, const Matrix* offsetMatrix)
	{
		//軸変換
		Matrix mBias;
		mBias.MakeRotationX(Math::PI * -0.5f);
		if (offsetMatrix != nullptr)
		{
			mBias = mBias * (*offsetMatrix);
		}
		m_stridingMeshInterface = std::make_unique< btTriangleIndexVertexArray>();
		//メッシュの番号
		int numMesh = 0;
		//メッシュに対してクエリ
		tkmFile.QueryMeshParts([&numMesh, &mBias](const TkmFile::SMesh& mesh) {
			//モデルの頂点バッファから、物理エンジン用の頂点バッファを作成
			VertexBufferPtr vertexBuffer = std::make_unique<VertexBuffer>();
			//メッシュの頂点バッファ分回す
			for (auto& vb : mesh.vertexBuffer)
			{
				auto pos = vb.pos;
				//バイアスをかける
				mBias.Apply(pos);
				vertexBuffer->push_back(pos);
			}
			//モデルのインデックスバッファから、物理エンジン用のインデックスバッファを作成
			IndexBufferPtr indexBuffer = std::make_unique<IndexBuffer>();
			//メッシュのバッファがからじゃないとき
			if (!mesh.indexBuffer16Array.empty())
			{
				//16bitインデックスバッファを作成する
				for (auto& ib : mesh.indexBuffer16Array)
				{
					for (auto index : ib.indices)
					{
						indexBuffer->push_back(index);
					}
				}
			}
			else
			{
				//32bitインデックスバッファを作成する
				for (auto& ib : mesh.indexBuffer32Array)
				{
					for (auto index : ib.indices)
					{
						indexBuffer->push_back(index);
					}
				}
			}
			//次のメッシュへ
			numMesh++;
		});

		//BulletPhysicsのインデックスメッシュを作成
		btIndexedMesh indexedMesh;
		IndexBuffer* ib = m_indexBufferArray.back().get();
		VertexBuffer* vb = m_vertexBufferArray.back().get();
		indexedMesh.m_numTriangles = (int)ib->size() / 3;
		indexedMesh.m_triangleIndexBase = (unsigned char*)(&ib->front());
		indexedMesh.m_triangleIndexStride = 12;
		indexedMesh.m_numVertices = (int)vb->size();
		indexedMesh.m_vertexBase = (unsigned char*)(&vb->front());
		indexedMesh.m_vertexStride = sizeof(Vector3);
		m_stridingMeshInterface->addIndexedMesh(indexedMesh);
	}

	//モデルからメッシュコライダーを生成
	void MeshCollider::CreateFromModel(const Model& model, const Matrix* offsetMatrix)
	{
		//モデルからtkmファイルを持ってきてCreateFromTkmFile関数を呼ぶ
		CreateFromTkmFile(model.GetTkmFile(), offsetMatrix);
	}
}