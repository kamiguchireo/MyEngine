#include "stdafx.h"
#include "Decale.h"

namespace Engine {
	
	//衝突した時に呼ばれる関数オブジェクト
	struct SweepResult : public btCollisionWorld::RayResultCallback
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
		
			isHit = true;
				
			if (rayResult.m_hitFraction < m_closestHitFraction)
			{
				//この衝突点の方が近いので、最近傍の衝突点を更新する。
				hitNormal = hitNormalTmp;
				m_closestHitFraction = rayResult.m_hitFraction;
			}
			
			return rayResult.m_hitFraction;
		}
	};

	Decale::Decale()
	{

	}

	Decale::~Decale()
	{

	}

	void Decale::Init()
	{
		//ユニークポインタを作成
		m_DecaleVP.reset(new Matrix[m_maxNum]);
		//ストラクチャーバッファを初期化
		m_STB.Init(
			sizeof(Matrix),
			m_maxNum,
			m_DecaleVP.get()
		);

		m_DecaleTex.InitFromDDSFile(L"Assets/Image/BulletDecale.dds");
		for (int i = 0; i < m_maxNum; i++)
		{
			m_DecaleVP[i] =
			{
			0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f
			};
		}
	}
	void Decale::Update()
	{
		m_STB.Update(m_DecaleVP.get());
	}

	void Decale::CalcVP(const Vector3& pos, const Vector3& right, const Vector3& dir)
	{
		//並行投影行列を作成
		Matrix m_proj = Matrix::Identity;

		m_proj.MakeOrthoProjectionMatrix(m_SideLength, m_SideLength, 0.0f, 10.0f);
		//レイを作成
		btVector3 start, end;
		start.setZero();
		end.setZero();
	
		//始点をセット
		start.setValue(pos.x, pos.y, pos.z);
		//終点となる位置を作成
		Vector3 EndPos = Vector3::Zero;
		//終点は始点となる位置に方向*距離を足したもの
		EndPos = pos;
		Vector3 Direction = Vector3::Zero;
		Direction = dir;
		//方向を正規化
		Direction.Normalize();
		//終点に方向に距離を掛けたもの足す
		EndPos += Direction * Distance;
		//終点をセット
		end.setValue(EndPos.x, EndPos.y, EndPos.z);

		//衝突検出
		SweepResult callback;
		callback.startPos = pos;
		//衝突検出
		g_engine->GetPhysicsWorld().RayTest(start, end, callback);
		callback.hasHit();
		if (callback.isHit)
		{
			btVector3 hitPosTmp = start + (end - start) * callback.m_closestHitFraction;
			//物理オブジェクトと衝突した
			Vector3 hitPos;
			hitPos.Set(hitPosTmp);
			//カメラを設置するために少し近づける
			hitPos -= Direction * 1.0f;
			//カメラ行列を作るためにターゲットポジションを作成
			Vector3 targetPos = hitPos;
			//ターゲットは少し離す
			targetPos += Direction * 1.0f;
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
			m_DecaleVP[num] = m_VP;
			if (num == m_maxNum)
			{
				num = 0;
			}
			else
			{
				num++;
			}
		}
		
	}
}