#pragma once
#include "ICollider.h"

namespace Engine {
	class BoxCollider :public ICollider
	{
	public:
		//�R���X�g���N�^
		BoxCollider();
		//�f�X�g���N�^
		~BoxCollider();

		//�{�b�N�X�R���C�_�[���쐬
		void Create(const Vector3& size);

		btCollisionShape* GetBody()const override
		{
			return shape;
		}

	private:
		btBoxShape* shape = NULL;
	};
}