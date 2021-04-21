#include "stdafx.h"
#include "PhysicsGhostObject.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

namespace Engine {
	void PhysicsGhostObject::Release()
	{
		//•¨—ƒ[ƒ‹ƒh‚É“o˜^‚³‚ê‚Ä‚¢‚é‚Æ‚«
		if (m_isRegistPhysicsWorld == true)
		{
			g_engine->GetPhysicsWorld().RemoveCollisionObject(m_ghostObject);
			m_isRegistPhysicsWorld = false;
		}
	}

	void PhysicsGhostObject::CreateCommon(Vector3 pos, Quaternion rot)
	{
		m_ghostObject.setCollisionShape(m_collider->GetBody());
		btTransform btTrans;
		btTrans.setOrigin({ pos.x,pos.y,pos.z });
		btTrans.setRotation({ rot.x,rot.y,rot.z });
		m_ghostObject.setWorldTransform(btTrans);
		
		//•¨—ƒ[ƒ‹ƒh‚É“o˜^
		g_engine->GetPhysicsWorld().AddCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = true;
	}

	void PhysicsGhostObject::UpdateWorldMatrix(const Vector3& pos, const Quaternion& rot)
	{
		btTransform btTrans;
		btTrans.setOrigin({ pos.x,pos.y,pos.z });
		btTrans.setRotation({ rot.x,rot.y,rot.z,rot.w });
		m_ghostObject.setWorldTransform(btTrans);
	}
}