#pragma once
#include "ICollider.h"

namespace Engine {
	class BoxCollider :public ICollider
	{
	public:
		//コンストラクタ
		BoxCollider();
		//デストラクタ
		~BoxCollider();

		//ボックスコライダーを作成
		void Create(const Vector3& size);

		btCollisionShape* GetBody()const override
		{
			return shape;
		}

	private:
		btBoxShape* shape = NULL;
	};
}