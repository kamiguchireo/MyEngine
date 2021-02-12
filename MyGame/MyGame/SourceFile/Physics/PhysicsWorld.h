#pragma once
#include "RigidBody.h"

namespace Engine {
	
	class CharacterController;
	class PhysicsWorld
	{
	public:
		~PhysicsWorld();
		//����������
		void Init();
		//�X�V����
		void Update();
		//�������
		void Release();
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
		std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfig;		//�R���W�����̐ݒ�
		std::unique_ptr<btCollisionDispatcher> m_collisionDispatcher;		//�Փˉ��������B
		std::unique_ptr<btBroadphaseInterface> m_overlappingPairCache;		//�u���[�h�t�F�[�Y�B�v�Z�R�X�g�̒Ⴂ��܂��ȏՓ˔���
		std::unique_ptr<btSequentialImpulseConstraintSolver> m_constraintSolver;		//�R���X�g���C���g�\���o�[�B�S�������̉��������B
		std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicWorld;		//���[���h�B
	};
}
