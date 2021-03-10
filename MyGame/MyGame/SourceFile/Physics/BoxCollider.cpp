#include "stdafx.h"
#include "BoxCollider.h"

namespace Engine {
	//コンストラクタ
	BoxCollider::BoxCollider()
	{
		
	}
	//デストラクタ
	BoxCollider::~BoxCollider()
	{
		if (shape != NULL)
		{
			delete shape;
		}
	}

	//ボックスコライダーを作成
	void BoxCollider::Create(const Vector3& size)
	{
		shape = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
	}
}