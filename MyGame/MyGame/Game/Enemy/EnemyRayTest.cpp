#include "stdafx.h"
#include "EnemyRayTest.h"


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