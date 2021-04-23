#pragma once

class btCollisionShape;

namespace Engine {
	class ICollider
	{
	public:
		ICollider()
		{
		}
		virtual ~ICollider()
		{

		}
		virtual btCollisionShape* GetBody()const = 0;
	};
}