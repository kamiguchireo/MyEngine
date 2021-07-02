#pragma once

class Enemy;
class EnemyRayTest
{
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

public:
	EnemyRayTest(Enemy* en) :m_enemy(en) {}
	~EnemyRayTest() {}

	bool Start();

	//pos		レイの始点
	//dir		レイの方向
	bool IsHit(Vector3& pos, Vector3& dir);

	void Update(Vector3 pl_pos);

private:	
	Enemy* m_enemy = nullptr;
	const float m_visualDist = 1000.0f;		//レイの範囲
	const float m_RayWaitTime = 0.5f;		//レイチェックする頻度
	float m_NowWaitTime = 0.0f;
	SweepResult callback;		//衝突検出
};