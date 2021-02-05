#pragma once
#include "ICollider.h"

namespace Engine {
	class CapsuleCollider : public ICollider
	{
	public:
		//作成
		void Create(float radius, float height)
		{

		}

		btCollisionShape* GetBody() const
		{
			return m_shape.get();
		}

	private:
		std::unique_ptr<btCapsuleShape> m_shape;		//カプセルコライダー
		float m_radius = 0.0f;		//半径
		float m_height = 0.0f;		//高さ
	};
}