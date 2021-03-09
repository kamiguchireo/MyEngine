#include "stdafx.h"
#include "PhysicsDebugDraw.h"

namespace Engine {
	void PhysicsDebugDraw::Init()
	{
		m_vs.LoadVS(L"Assets/shader/linePrimitive.fx", "VSMain");
		m_ps.LoadPS(L"Assets/shader/linePrimitive.fx", "PSMain");
		//m_cb.Create(nullptr, sizeof(SConstantBuffer));
	}
}