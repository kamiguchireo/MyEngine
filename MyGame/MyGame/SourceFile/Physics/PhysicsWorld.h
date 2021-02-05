#pragma once
#include "RigidBody.h"

namespace Engine {
	
	class CharacterController;
	class PhysicsWorld
	{
	public:
		~PhysicsWorld();

		//���̂�ǉ�
		void AddRigidBody(RigidBody& rb)
		{
			//�t�B�W�b�N�X���[���h�ɓo�^����Ă��Ȃ��Ƃ�
			if (rb.IsAddPhysicsWorld() == false)
			{
				m_dynamicWorld->addRigidBody(rb.GetBody());
				rb.SetMarkAddPhysicsWorld();
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
		std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicWorld;		//���[���h�B
	};
}
