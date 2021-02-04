#pragma once

class btCollisionShape;

namespace Engine {
	class ICollider
	{
	public:
		virtual btCollisionShape* GetBody()const = 0;
	};
}