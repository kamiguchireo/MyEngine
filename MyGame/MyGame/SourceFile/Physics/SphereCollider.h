#pragma once
#include "ICollider.h"

namespace Engine {
	class SphereCollider :public ICollider
	{
	public:
		//�R���X�g���N�^
		SphereCollider();
		//�f�X�g���N�^
		~SphereCollider();

		//���̃R���C�_�[���쐬
		//radius		���a
		void Create(const float radius);

		btCollisionShape* GetBody()const
		{
			return shape;
		}

	private:
		btSphereShape* shape = NULL;
	};
}