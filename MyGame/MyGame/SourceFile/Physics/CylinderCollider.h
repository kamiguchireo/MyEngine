#pragma once
#include "ICollider.h"

namespace Engine {
	class CylinderCollider:public ICollider
	{
	public:
		CylinderCollider();
		~CylinderCollider();

		//円柱コライダーを作成
		void Create(Vector3&vec);

	private:
		btCylinderShape* shape = NULL;

	};
}