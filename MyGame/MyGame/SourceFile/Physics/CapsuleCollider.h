#pragma once
#include "ICollider.h"

namespace Engine {
	class CapsuleCollider : public ICollider
	{
	public:
		//作成
		//radius		半径
		//height		高さ
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

		//半径
		float GetRadius()const
		{
			return m_radius;
		}
		//高さ
		float GetHeight()const
		{
			return m_height;
		}
	private:
		std::unique_ptr<btCapsuleShape> m_shape;		//カプセルコライダー
		float m_radius = 0.0f;		//半径
		float m_height = 0.0f;		//高さ
	};
}