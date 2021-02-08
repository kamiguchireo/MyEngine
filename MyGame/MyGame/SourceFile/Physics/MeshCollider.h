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
		
		//tkm�t�@�C�����烁�b�V���R���C�_�[�𐶐�
		//tkmFile		tkm�t�@�C��
		void CreateFromTkmFile(const TkmFile& tkmFile, const Matrix* offsetMatrix);
		//���f�����烁�b�V���R���C�_�[�𐶐�
		//model		�X�L�����f��
		void CreateFromModel(const Model& model, const Matrix* offsetMatrix);

		btCollisionShape* GetBody() const override
		{
			return m_meshShape.get();
		}

	private:
		std::unique_ptr<btTriangleIndexVertexArray> m_stridingMeshInterface;
		typedef std::vector<Vector3> VertexBuffer;		//���_�o�b�t�@�B
		typedef std::unique_ptr<VertexBuffer> VertexBufferPtr;
		std::vector<VertexBufferPtr> m_vertexBufferArray;		//���_�o�b�t�@�̔z��B
		typedef std::vector<unsigned int> IndexBuffer;		//�C���f�b�N�X�o�b�t�@�B
		typedef std::unique_ptr<IndexBuffer> IndexBufferPtr;
		std::vector<IndexBufferPtr> m_indexBufferArray;		//�C���f�b�N�X�o�b�t�@�̔z��B
		std::unique_ptr<btBvhTriangleMeshShape> m_meshShape;		//���b�V���`��
	};
}