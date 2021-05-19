#include "stdafx.h"
#include "Decale.h"

namespace Engine {
	
	//衝突した時に呼ばれる関数オブジェクト
	struct SweepResult : public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;						//衝突フラグ。
		Vector3 hitNormal = Vector3::Zero;	//衝突点の法線。

		//衝突したときに呼ばれるコールバック関数。
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool /*normalInWorldSpace*/)
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

	void Decale::CalcVP(const btVector3& start, const btVector3& end)
	{
		//並行投影行列を作成
		Matrix m_proj = Matrix::Identity;

		m_proj.MakeOrthoProjectionMatrix(m_SideLength, m_SideLength, 0.0f, 10.0f);

		//衝突検出
		SweepResult callback;
		//衝突検出
		g_engine->GetPhysicsWorld().RayTest(start, end, callback);

		//レイが衝突しているとき
		if (callback.isHit)
		{
			//当たった位置
			btVector3 hitPosTmp = start + (end - start) * callback.m_closestHitFraction;
			//当たった位置の法線
			Vector3 hitNormal = callback.hitNormal;

			//カメラの視点
			Vector3 CameraPos = Vector3::Zero;
			//カメラの注視点
			Vector3 CameraTarget = Vector3::Zero;

			//セット
			CameraPos.Set(hitPosTmp);
			CameraTarget.Set(hitPosTmp);

			//カメラの視点なので法線方向に移動する
			CameraPos += hitNormal;
			//カメラの注視点なので法線の逆方向に移動する
			CameraTarget -= hitNormal;

			//カメラ行列を作成
			Matrix m_view = Matrix::Identity;

			//視点から注視点へのベクトル
			Vector3 PosToTarget = CameraTarget - CameraPos;
			//正規化
			PosToTarget.Normalize();

			//カメラの向きがほとんど真上か真下の時
			if (PosToTarget.y >= 0.99 || PosToTarget.y <= -0.99)
			{
				//{1.0f,0.0f,0.0f}を上方向としてカメラ行列を作成
				m_view.MakeLookAt(CameraPos, CameraTarget, Vector3::Right);
			}
			else
			{
				//それ以外の時
				//{0.0f,1.0f,0.0f}を上方向としてカメラ行列を作成
				m_view.MakeLookAt(CameraPos, CameraTarget, Vector3::Up);
			}
			//ビュープロジェ行列
			Matrix m_VP = Matrix::Identity;
			m_proj.Multiply(m_view, m_proj);
			m_VP = m_proj;
			m_DecaleVP[num] = m_VP;
			//現在のデカールの番号を増やす
			num++;
			//最大値になっていたら0に戻す
			num %= m_maxNum;
		}
		
	}
}