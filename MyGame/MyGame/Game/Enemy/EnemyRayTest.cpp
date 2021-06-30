#include "stdafx.h"
#include "EnemyRayTest.h"

//衝突した時に呼ばれる関数オブジェクト
struct SweepResult : public btCollisionWorld::RayResultCallback
{
	bool isHit = false;						//衝突フラグ。
	btScalar ObjectNearDist = 10000.0;
	btScalar GhostDist = 10000.0;
	//衝突したときに呼ばれるコールバック関数。
	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool /*normalInWorldSpace*/)
	{
		if (rayResult.m_collisionObject->getUserIndex() == enCollisionAttr_StaticObject)
		{
			//スタティックオブジェクトにぶつかったとき
			if (rayResult.m_hitFraction < ObjectNearDist)
			{
				ObjectNearDist = rayResult.m_hitFraction;
			}
			return 0.0f;
		}
		else if (rayResult.m_collisionObject->getUserIndex() == enCollisionAttr_Player)
		{
			//プレイヤーにぶつかったとき
			if (rayResult.m_hitFraction < GhostDist)
			{
				GhostDist = rayResult.m_hitFraction;
			}
			m_collisionObject = rayResult.m_collisionObject;
			//衝突点の法線
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(rayResult.m_hitNormalLocal);

			isHit = true;

			if (rayResult.m_hitFraction < m_closestHitFraction)
			{
				//この衝突点の方が近いので、最近傍の衝突点を更新する。
				m_closestHitFraction = rayResult.m_hitFraction;
			}

			return rayResult.m_hitFraction;
		}

		return rayResult.m_hitFraction;
	}
};

bool EnemyRayTest::Start()
{

	return true;
}

bool EnemyRayTest::IsHit(Vector3& pos, Vector3& dir)
{
	//レイを作成
	btVector3 start, end;
	start.setZero();
	end.setZero();

	//始点をセット
	start.setValue(pos.x, pos.y, pos.z);
	//終点を計算
	Vector3 EndPos = Vector3::Zero;
	//始点を代入
	EndPos = pos;
	//見ている方向に距離を掛けたものを加算
	EndPos += dir * m_visualDist;
	end.setValue(EndPos.x, EndPos.y, EndPos.z);

	//衝突検出
	SweepResult callback;
	g_engine->GetPhysicsWorld().RayTest(start, end, callback);
	//レイがゴーストオブジェクトにヒットしているとき
	if (callback.isHit)
	{
		//オブジェクトの手前に何もないとき
		if (callback.GhostDist < callback.ObjectNearDist)
		{
			//ヒットしているのでtrueを返す
			return true;
		}
	}

	//ヒットしていないのでfalseを返す
	return false;
}