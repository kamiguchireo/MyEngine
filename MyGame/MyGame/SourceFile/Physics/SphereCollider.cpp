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

	//球体コライダーを作成
	void SphereCollider::Create(const float radius)
	{
		shape = new btSphereShape(radius);
	}

}