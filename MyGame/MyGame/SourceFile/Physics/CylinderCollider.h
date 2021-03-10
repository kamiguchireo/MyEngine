#pragma once
#include "ICollider.h"

namespace Engine {
	class CylinderCollider:public ICollider
	{
	public:
		CylinderCollider();
		~CylinderCollider();

		//�~���R���C�_�[���쐬
		void Create(Vector3&vec);

		btCollisionShape* GetBody()const
		{
			return shape;
		}
	private:
		btCylinderShape* shape = NULL;

	};
}