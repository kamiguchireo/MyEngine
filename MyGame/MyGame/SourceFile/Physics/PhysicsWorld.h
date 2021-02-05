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
		//���̂��폜
		void RemoveRigidBody(RigidBody& rb)
		{
			//�t�B�W�b�N�X���[���h�ɓo�^����Ă���Ƃ�
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
		std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicWorld;		//���[���h�B
	};
}
