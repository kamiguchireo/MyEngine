#include "stdafx.h"
#include "PhysicsWorld.h"
#include "CharacterController.h"
#include "PhysicsDebugDraw.h"

namespace Engine {

	namespace {
		struct MyContactResultCallback :public btCollisionWorld::ContactResultCallback {
			using ContantTestCallback = std::function<void(const btCollisionObject& contactCollisionObject)>;
			ContantTestCallback m_cb;
			btCollisionObject* m_me = nullptr;
			virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
			{
				if (m_me == colObj0Wrap->getCollisionObject())
				{
					m_cb(*colObj1Wrap->getCollisionObject());
				}
				return 0.0f;
			}
		};
	}
	PhysicsWorld::~PhysicsWorld()
	{
		Release();
		if (m_physicsDebugDraw != nullptr)
		{
			delete m_physicsDebugDraw;
		}
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

		//ï®óùÉGÉìÉWÉìÇèâä˙âª
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

		//èdóÕÇÃê›íË
		m_dynamicWorld->setGravity(btVector3(0, -10, 0));

		m_physicsDebugDraw = new Engine::PhysicsDebugDraw();
		m_physicsDebugDraw->Init();
	}

	void PhysicsWorld::Update()
	{
		m_dynamicWorld->stepSimulation(g_gameTime.GetFrameDeltaTime());
	}

	void PhysicsWorld::DebugDrawWorld()
	{
		m_physicsDebugDraw->BeginDraw();
		m_dynamicWorld->setDebugDrawer(m_physicsDebugDraw);
		m_dynamicWorld->debugDrawWorld();
		m_physicsDebugDraw->EndDraw();
	}
}