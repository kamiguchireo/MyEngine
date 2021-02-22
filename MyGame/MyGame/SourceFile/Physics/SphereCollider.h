#pragma once
#include "ICollider.h"

namespace Engine {
	class SphereCollider :public ICollider
	{
	public:
		//コンストラクタ
		SphereCollider();
		//デストラクタ
		~SphereCollider();

		//球体コライダーを作成
		//radius		半径
		void Create(const float radius);

		btCollisionShape* GetBody()const
		{
			return shape;
		}

	private:
		btSphereShape* shape = NULL;
	};
}