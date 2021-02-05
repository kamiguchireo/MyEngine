#pragma once
#include "ICollider.h"

namespace Engine {
	class CapsuleCollider : public ICollider
	{
	public:
		//�쐬
		//radius		���a
		//height		����
		void Create(float radius, float height)
		{
			m_shape = std::make_unique<btCapsuleShape>(radius, height);
			m_radius = radius;
			m_height = height;
		}

		btCollisionShape* GetBody() const
		{
			return m_shape.get();
		}

		//���a
		float GetRadius()const
		{
			return m_radius;
		}
		//����
		float GetHeight()const
		{
			return m_height;
		}
	private:
		std::unique_ptr<btCapsuleShape> m_shape;		//�J�v�Z���R���C�_�[
		float m_radius = 0.0f;		//���a
		float m_height = 0.0f;		//����
	};
}