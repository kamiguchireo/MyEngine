#pragma once
#include "RigidBody.h"

namespace Engine {
	
	class CharacterController;
	class PhysicsDebugDraw;
	class PhysicsWorld
	{
	public:
		~PhysicsWorld();
		//初期化処理
		void Init();
		//更新処理
		void Update();
		void DebugDrawWorld();
		//解放処理
		void Release();
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

		//コリジョンオブジェクトをワールドに登録
		void AddCollisionObject(btCollisionObject& colliObj)
		{
			m_dynamicWorld->addCollisionObject(&colliObj);
		}

		//コリジョンオブジェクトをワールドから削除
		void RemoveCollisionObject(btCollisionObject& colliObj)
		{
			m_dynamicWorld->removeCollisionObject(&colliObj);
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
		class btIDebugDraw* m_debugDraw;
		std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfig;		//コリジョンの設定
		std::unique_ptr<btCollisionDispatcher> m_collisionDispatcher;		//衝突解決処理。
		std::unique_ptr<btBroadphaseInterface> m_overlappingPairCache;		//ブロードフェーズ。計算コストの低い大まかな衝突判定
		std::unique_ptr<btSequentialImpulseConstraintSolver> m_constraintSolver;		//コンストレイントソルバー。拘束条件の解決処理。
		std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicWorld;		//ワールド。
		Engine::PhysicsDebugDraw* m_physicsDebugDraw = nullptr;
	};
}
