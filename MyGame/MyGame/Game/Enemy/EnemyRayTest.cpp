#include "stdafx.h"
#include "EnemyRayTest.h"
#include "Enemy.h"

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

void EnemyRayTest::Update(Vector3 pl_pos)
{		
	//現在の時間を加算
	m_NowWaitTime += g_gameTime.GetFrameDeltaTime();
	//一定時間ごとにレイテスト
	if (m_NowWaitTime >= m_RayWaitTime)
	{

		if (m_enemy->CanSeePlayer())
		{
			Vector3 enemyPos = m_enemy->GetPosition();
			//レイの始点
			Vector3 RayStart = enemyPos;
			//高さを最低限確保
			RayStart.y += 50.0f;
			//レイの方向
			Vector3 RayDir = pl_pos - enemyPos;
			RayDir.Normalize();

			//プレイヤーに向けてレイを飛ばして間に何もないとき
			if (IsHit(RayStart, RayDir))
			{
				//プレイヤーを発見した状態にする
				m_enemy->ChangeActState(EnemyActState::enState_Discover);
			}
			else
			{
				m_enemy->ChangeActState(EnemyActState::enState_Normal);
			}
			//カウントを0にする
			m_NowWaitTime = 0.0f;
		}

	}
}