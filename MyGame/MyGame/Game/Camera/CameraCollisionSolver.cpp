#include "stdafx.h"
#include "CameraCollisionSolver.h"

namespace Engine {
	struct SConvexSweepCallback :public btCollisionWorld::ClosestConvexResultCallback
	{
	public:
		Vector3 m_rayDir;		//レイの方向
		//コンストラクタ
		SConvexSweepCallback(Vector3 rayDir) :
			btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f)),
			m_rayDir(rayDir) {}

		virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			Vector3 normal;
			normal.Set(convexResult.m_hitNormalLocal);

			return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
		}
	};
	CameraCollisionSolver::CameraCollisionSolver()
	{

	}

	CameraCollisionSolver::~CameraCollisionSolver()
	{

	}

	void CameraCollisionSolver::Init(float radius)
	{
		m_radius = radius;
		m_collider.Create(radius);
		m_isInited = true;		//初期化済みのフラグを立てる
	}

	bool CameraCollisionSolver::Execute(Vector3& result, const Vector3& position, const Vector3& target)
	{
		if (m_isInited == false)
		{		
			//初期化を行ってください
			std::abort();

			return false;
		}

		result = position;
		//視点から注視点へのベクトル
		Vector3 vWk;
		vWk.Subtract(target, position);
		if (vWk.LengthSq() < FLT_EPSILON)
		{
			//視点と注視点がほぼ同じ座標にある
			return false;
		}

		//正規化
		vWk.Normalize();
		//レイを作成する
		btTransform btStart, btEnd;
		//初期化
		btStart.setIdentity();
		btEnd.setIdentity();
		btStart.setOrigin(btVector3(target.x, target.y, target.z));
		btEnd.setOrigin(btVector3(position.x, position.y, position.z));

		SConvexSweepCallback callback(vWk);

		g_engine->GetPhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), btStart, btEnd, callback);
		if (callback.hasHit())
		{
			Vector3 vHitPos = Vector3::Zero;
			vHitPos.Set(callback.m_hitPointWorld);
			Vector3 vOffset = Vector3::Zero;
			vOffset.Set(callback.m_hitNormalWorld);
			vOffset.Scale(m_radius);
			result.Add(vHitPos, vOffset);

			return true;
		}

		return false;
	}
}