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
		bool isHit = false;						//衝突フラグ。
		Vector3 hitPos = Vector3::Zero;		//衝突点。
		Vector3 startPos = Vector3::Zero;		//レイの始点。
		float dist = FLT_MAX;					//衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値。
		Vector3 hitNormal = Vector3::Zero;	//衝突点の法線。
		btCollisionObject* me = nullptr;		//自分自身。自分自身との衝突を除外するためのメンバ。

		//衝突したときに呼ばれるコールバック関数。
		virtual btScalar addSignalResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			//自分か地面に衝突したとき
			if (convexResult.m_hitCollisionObject == me
				|| convexResult.m_hitCollisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT
				)
			{
				return 0.0f;
			}
			//衝突点の法線
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(convexResult.m_hitNormalLocal);
			//上方向と衝突点の法線のなす角度を求める。
			float angle = fabsf(acosf(hitNormalTmp.Dot(Vector3::Up)));
			//地面の傾斜が54度以上なので壁とみなす。
			if (angle >= Math::PI * 0.3f)
			{
				isHit = true;
				Vector3 hitPosTmp;
				hitPosTmp.Set(convexResult.m_hitPointLocal);
				//交点との距離を調べる。
				Vector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				vDist.y = 0.0f;
				float distTmp = vDist.Length();
				if (distTmp < dist) 
				{
					//この衝突点の方が近いので、最近傍の衝突点を更新する。
					hitPos = hitPosTmp;
					dist = distTmp;
					hitNormal = hitNormalTmp;
				}
			}
			return 0.0f;
		}
	};

	void CharacterController::Init(float radius, float height, const Vector3& position)
	{
		//位置を代入
		m_position = position;
		//半径を代入
		m_radius = radius;
		//高さを代入
		m_height = height;
		//コリジョン作成
		m_collider.Create(radius, height);

		//剛体を初期化
		RigidBodyInfo rbInfo;
		//コライダーを代入
		rbInfo.collider = &m_collider;
		//質量を代入
		rbInfo.mass = 0.0f;
		//剛体を作成
		m_rigidBody.Create(rbInfo);
		btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
		//剛体の位置を更新
		trans.setOrigin(btVector3(position.x, position.y + m_height * 0.5f + m_radius, position.z));
		m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		//g_graphicsEngine->GetPhysicsWorld() .AddRigidBody(m_rigidBody);
		m_isInited = true;
	}
}
