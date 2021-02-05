#include "stdafx.h"
#include "PhysicsStaticObject.h"

namespace Engine {
	void PhysicsStaticObject::Release()
	{
		g_graphicsEngine->GetPhysicsWorld().RemoveRigidBody(m_rigidBody);
	}

	void PhysicsStaticObject::CreateCommon(Vector3 pos, Quaternion rot)
	{
		RigidBodyInfo rbInfo;
		rbInfo.collider = m_collider.get();
		rbInfo.mass = 0.0f;
		rbInfo.pos = pos;
		rbInfo.rot = rot;
		m_rigidBody.Create(rbInfo);
		g_graphicsEngine->GetPhysicsWorld().AddRigidBody(m_rigidBody);
	}
}