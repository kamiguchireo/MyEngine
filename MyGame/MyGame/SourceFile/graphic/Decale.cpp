#include "stdafx.h"
#include "Decale.h"

namespace Engine {
	//衝突したときに呼ばれる関数オブジェクト(地面用)
	struct SweepResultGround : public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;		//衝突フラグ
		Vector3 hitPos = Vector3(0.0f, -FLT_MAX, 0.0f);		//衝突点
		Vector3 startPos = Vector3::Zero;		//レイの始点
		Vector3 hitNormal = Vector3::Zero;		//衝突点の法線
		float dist = FLT_MAX;		//衝突点までの距離。一番近い衝突点を求めるため。
		
		//衝突したときに呼ばれるコールバック関数
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
		{
			//自分に衝突したとき
			if (rayResult.m_collisionObject->getUserIndex() == enCollisionAttr_Character
				||rayResult.m_collisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT
				)
			{
				return 0.0f;
			}

			//衝突点の法線
			Vector3 hitNormalTmp = *(Vector3*)&rayResult.m_hitNormalLocal;
			//上方向と法線のなす角を求める
			float angle = hitNormalTmp.Dot(Vector3::Up);
			angle = fabsf(acosf(angle));
			//地面の傾斜が54度より小さいので地面とみなす
			if (angle < Math::PI * 0.3f)
			{
				//衝突している
				isHit = true;
				Vector3 hitPosTmp = *(Vector3*)&rayResult.m_hitNormalLocal;
				//衝突点の距離を求める
				Vector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (dist > distTmp)
				{
					//この衝突点のほうが近いので、最近傍の衝突点を更新する
					hitPos = hitPosTmp;
					hitNormal = *(Vector3*)&rayResult.m_hitNormalLocal;
					dist = distTmp;
				}
			}
			return 0.0f;
		}
	};
	//衝突した時に呼ばれる関数オブジェクト(壁用)
	struct SweepResultWall : public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;						//衝突フラグ。
		Vector3 hitPos = Vector3::Zero;		//衝突点。
		Vector3 startPos = Vector3::Zero;		//レイの始点。
		float dist = FLT_MAX;					//衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値。
		Vector3 hitNormal = Vector3::Zero;	//衝突点の法線。

		//衝突したときに呼ばれるコールバック関数。
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
		{
			//自分か地面に衝突したとき
			if (rayResult.m_collisionObject->getUserIndex() == enCollisionAttr_Character
				||rayResult.m_collisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT)
			{
				return 0.0f;
			}
			//衝突点の法線
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(rayResult.m_hitNormalLocal);
			//上方向と衝突点の法線のなす角度を求める。
			float angle = fabsf(acosf(hitNormalTmp.Dot(Vector3::Up)));
			//地面の傾斜が54度以上なので壁とみなす。
			if (angle >= Math::PI * 0.3f)
			{
				isHit = true;
				Vector3 hitPosTmp;
				hitPosTmp.Set(rayResult.m_hitNormalLocal);
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

	Decale::Decale()
	{

	}

	Decale::~Decale()
	{

	}

	void Decale::Update()
	{
		//並行投影行列を作成
		Matrix m_proj = Matrix::Identity;
		m_proj.MakeOrthoProjectionMatrix(10.0f, 10.0f, 0.0f, 10.0f);
		//レイを作成
		btVector3 start, end;
		start.setZero();
		end.setZero();
		for (int i = 0; i < PosNum; i++)
		{
			//始点をセット
			start.setValue(m_StartPos[i].x, m_StartPos[i].y, m_StartPos[i].z);
			//終点となる位置を作成
			Vector3 EndPos = Vector3::Zero;
			//終点は始点となる位置に方向*距離を足したもの
			EndPos = m_StartPos[i];
			Vector3 Direction = Vector3::Zero;
			Direction = m_Direction[i];
			//方向を正規化
			Direction.Normalize();
			//正規化した方向に距離をかける
			Direction *= Distance;
			//終点に足す
			EndPos += Direction;
			//終点をセット
			end.setValue(EndPos.x, EndPos.y, EndPos.z);

			//衝突検出
			SweepResultWall callback;
			callback.startPos = m_StartPos[i];
			//衝突検出
			g_engine->GetPhysicsWorld().RayTest(start, end, callback);

			if (callback.isHit)
			{
				btVector3 hitPosTmp = start + (end - start) * callback.m_closestHitFraction;
				//物理オブジェクトと衝突した
				Vector3 hitPos;
				hitPos.Set(hitPosTmp);
				//カメラを設置するために少し近づける
				hitPos -= Direction * 5.0f;
				//カメラ行列を作るためにターゲットポジションを作成
				Vector3 targetPos = callback.hitPos;
				//ターゲットは少し離す
				targetPos += Direction * 5.0f;
				//カメラ行列を作成
				Matrix m_view = Matrix::Identity;
				//カメラの前方向
				Vector3 cameraForward = Vector3::Front;
				cameraForward = g_camera3D->GetForward();
				//カメラの右方向
				Vector3 ViewRight = Vector3::Right;
				ViewRight.Cross(Direction, cameraForward);
				//正規化
				ViewRight.Normalize();
				//カメラの上方向
				Vector3 CameraUpAxis = Vector3::Up;
				CameraUpAxis.Cross(ViewRight, Direction);
				//正規化
				CameraUpAxis.Normalize();

				//カメラ行列を作成
				m_view.MakeLookAt(hitPos, targetPos, CameraUpAxis);

				Matrix m_VP = Matrix::Identity;
				m_proj.Multiply(m_view, m_proj);
				m_VP = m_proj;
				m_DecaleVP.push_back(m_VP);
			}
		}
	}
}