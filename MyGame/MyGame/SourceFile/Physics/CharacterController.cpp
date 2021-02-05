#include "stdafx.h"
#include "CharacterController.h"

namespace Engine {
	//衝突したときに呼ばれる関数オブジェクト(地面用)
	struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;		//衝突フラグ
		Vector3 hitPos = Vector3(0.0f, -FLT_MAX, 0.0f);		//衝突点
		Vector3 startPos = Vector3::Zero;		//レイの始点
		Vector3 hitNormal = Vector3::Zero;		//衝突点の法線
		btCollisionObject* me = nullptr;		//自分自身。自分自身との衝突を回避するためのメンバ
		float dist = FLT_MAX;		//衝突店までの距離。一番近い衝突点を求めるため。
																		
		//衝突したときに呼ばれるコールバック関数
		virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			//自分に衝突したとき
			if (convexResult.m_hitCollisionObject == me
				|| convexResult.m_hitCollisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT
				)
				{
				return 0.0f;
			}

			//衝突点の法線
			Vector3 hitNormalTmp = *(Vector3*)&convexResult.m_hitNormalLocal;
			//上方向と法線のなす角を求める
			float angle = hitNormalTmp.Dot(Vector3::Up);
			angle = fabsf(acosf(angle));
			//地面の傾斜が54度より小さいので地面とみなす
			if (angle < Math::PI * 0.3f)
			{
				//衝突している
				isHit = true;
				Vector3 hitPosTmp = *(Vector3*)&convexResult.m_hitPointLocal;
				//衝突点の距離を求める
				Vector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (dist > distTmp)
				{
					//この衝突点のほうが近いので、最近傍の衝突点を更新する
					hitPos = hitPosTmp;
					hitNormal = *(Vector3*)&convexResult.m_hitNormalLocal;
					dist = distTmp;
				}
			}
			return 0.0f;
		}
	};
	//衝突した時に呼ばれる関数オブジェクト(壁用)
	struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
	{

	};
}
