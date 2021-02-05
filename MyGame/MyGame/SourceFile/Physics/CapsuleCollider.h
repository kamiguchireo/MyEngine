#pragma once
#include "ICollider.h"

namespace Engine {
	class CapsuleCollider : public ICollider
	{
	public:
		//�쐬
		void Create(float radius, float height)
		{

		}

		btCollisionShape* GetBody() const
		{
			return m_shape.get();
		}

	private:
		std::unique_ptr<btCapsuleShape> m_shape;		//�J�v�Z���R���C�_�[
		float m_radius = 0.0f;		//���a
		float m_height = 0.0f;		//����
	};
}