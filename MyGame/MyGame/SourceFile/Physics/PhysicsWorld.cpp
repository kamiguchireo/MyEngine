#include "stdafx.h"
#include "PhysicsWorld.h"

namespace Engine {
	PhysicsWorld::~PhysicsWorld()
	{
		Release();
	}

	void PhysicsWorld::Release()
	{
		m_dynamicWorld.reset();
		m_constraintSolver.reset();
		m_overlappingPairCache.reset();
		m_collisionDispatcher.reset();
		m_collisionConfig.reset();
	}

	void PhysicsWorld::Init()
	{
		Release();

		//•¨—ƒGƒ“ƒWƒ“‚ğ‰Šú‰»
		m_collisionConfig = std::make_unique<btDefaultCollisionConfiguration>();

		m_collisionDispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfig.get());
		
		m_overlappingPairCache = std::make_unique<btDbvtBroadphase>();

		m_constraintSolver = std:: make_unique<btSequentialImpulseConstraintSolver>();

		m_dynamicWorld = std::make_unique<btDiscreteDynamicsWorld>(
			m_collisionDispatcher.get(),
			m_overlappingPairCache.get(),
			m_constraintSolver.get(),
			m_collisionConfig.get()
			);

		//d—Í‚Ìİ’è
		m_dynamicWorld->setGravity(btVector3(0, -10, 0));

	}

	void PhysicsWorld::Update()
	{
		m_dynamicWorld->stepSimulation(g_gameTime.GetFrameDeltaTime());
	}
}