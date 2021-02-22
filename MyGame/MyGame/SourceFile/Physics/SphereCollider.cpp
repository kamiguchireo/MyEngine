#include "stdafx.h"
#include "SphereCollider.h"

namespace Engine {
	SphereCollider::SphereCollider()
	{

	}

	SphereCollider::~SphereCollider()
	{
		if (shape != NULL)
		{
			delete shape;
			shape = NULL;
		}
	}

	//���̃R���C�_�[���쐬
	void SphereCollider::Create(const float radius)
	{
		shape = new btSphereShape(radius);
	}

}