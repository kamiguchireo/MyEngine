#pragma once
#include "RigidBody.h"

namespace Engine {
	
	class CharacterController;
	class PhysicsWorld
	{
	public:
		~PhysicsWorld();

		//剛体を追加
		void AddRigidBody(RigidBody& rb)
		{
			//フィジックスワールドに登録されていないとき
			if (rb.IsAddPhysicsWorld() == false)
			{
				m_dynamicWorld->addRigidBody(rb.GetBody());
				rb.SetMarkAddPhysicsWorld();
			}
		}
		//剛体を削除
		void RemoveRigidBody(RigidBody& rb)
		{
			//フィジックスワールドに登録されているとき
			if (rb.IsAddPhysicsWorld() == true)
			{
				m_dynamicWorld->removeRigidBody(rb.GetBody());
				rb.SetUnmarkAddPhysicsWorld();
			}
		}
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convexToWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
		)
		{
			m_dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
		}

	private:
		std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicWorld;		//ワールド。
	};
}
