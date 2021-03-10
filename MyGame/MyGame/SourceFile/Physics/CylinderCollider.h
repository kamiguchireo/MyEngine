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

	private:
		btCylinderShape* shape = NULL;

	};
}