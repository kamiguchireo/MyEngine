#include "stdafx.h"
#include "BoxCollider.h"

namespace Engine {
	//�R���X�g���N�^
	BoxCollider::BoxCollider()
	{
		
	}
	//�f�X�g���N�^
	BoxCollider::~BoxCollider()
	{
		if (shape != NULL)
		{
			delete shape;
		}
	}

	//�{�b�N�X�R���C�_�[���쐬
	void BoxCollider::Create(const Vector3& size)
	{
		shape = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
	}
}