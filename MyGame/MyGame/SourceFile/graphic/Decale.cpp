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
		m_DecaleTex.InitFromDDSFile(L"Assets/Image/Bullet_hole.dds");
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
		//Vector3 v[8] = {Vector3::Zero };

		//for (int i = 0; i < PosNum; i++)
		//{
		//	Vector3 toNear, toFar = { Vector3::Zero };
		//	//AABB手前の座標
		//	toNear = m_StartPos[i];
		//	//AABB奥の座標
		//	toFar = m_StartPos[i] + m_Direction[i] * Distance;
		//	//上方向
		//	Vector3 toUp = Vector3::Zero;
		//	toUp = Cross(m_Direction[i], m_Right[i]);
		//	//加算する右方向
		//	Vector3 AddRightPos = m_Right[i] * m_SideLength;
		//	//加算する上方向
		//	Vector3 AddUpPos = toUp * m_SideLength;

		//	//AABBを作成する
		//	//手前右上の座標
		//	v[0] = toNear + AddRightPos + AddUpPos;
		//	//手前右下の座標
		//	v[1] = v[0] - (AddUpPos * 2.0f);
		//	//手前左上の座標
		//	v[2] = toNear - AddRightPos + AddUpPos;
		//	//手前左下の座標
		//	v[3] = v[2] - (AddUpPos * 2.0f);

		//	//奥右上の座標
		//	v[4] = toFar + AddRightPos + AddUpPos;
		//	//奥右下の座標
		//	v[5] = v[4] - (AddUpPos * 2.0f);
		//	//奥左上の座標
		//	v[6] = toFar - AddRightPos + AddUpPos;
		//	//奥左下の座標
		//	v[7] = v[6] - (AddUpPos * 2.0f);

		//	//カメラ行列を作成
		//	Matrix DecaleView = Matrix::Identity;
		//	//カメラの横をセット
		//	DecaleView.m[0][0] = m_Right[i].x;
		//	DecaleView.m[0][1] = m_Right[i].y;
		//	DecaleView.m[0][2] = m_Right[i].z;
		//	DecaleView.m[0][3] = 0.0f;
		//	//カメラの上をセット
		//	DecaleView.m[1][0] = toUp.x;
		//	DecaleView.m[1][1] = toUp.y;
		//	DecaleView.m[1][2] = toUp.z;
		//	DecaleView.m[1][3] = 0.0f;
		//	//カメラの前をセット
		//	DecaleView.m[2][0] = m_Direction[i].x;
		//	DecaleView.m[2][1] = m_Direction[i].y;
		//	DecaleView.m[2][2] = m_Direction[i].z;
		//	DecaleView.m[2][3] = 0.0f;
		//	//カメラのポジションをセット
		//	DecaleView.m[3][0] = m_StartPos[i].x;
		//	DecaleView.m[3][1] = m_StartPos[i].y;
		//	DecaleView.m[3][2] = m_StartPos[i].z;
		//	DecaleView.m[3][3] = 1.0f;
		//	//カメラビュー完成
		//	DecaleView.Inverse(DecaleView);

		//	//視推台を構成する8頂点を計算できたので、ライト空間に座標を変換して、AABBを求める
		//	Vector3 vMax = { -FLT_MAX,-FLT_MAX,-FLT_MAX };
		//	Vector3 vMin = { FLT_MAX, FLT_MAX, FLT_MAX };
		//	for (auto& vInLight : v)
		//	{
		//		//ベクトルと行列の乗算
		//		DecaleView.Apply(vInLight);
		//		//最大値を設定
		//		vMax.Max(vInLight);
		//		//最小値を設定
		//		vMin.Min(vInLight);
		//	}
		//	//幅と高さ
		//	float w = vMax.x - vMin.x;
		//	float h = vMax.y - vMin.y;
		//	float far_z = -1.0f;
		//	far_z = vMax.z;

		//	Matrix m_proj = Matrix::Identity;
		//	m_proj.MakeOrthoProjectionMatrix(
		//		w,
		//		h,
		//		far_z / Distance,
		//		far_z
		//	);
		//	Matrix m_VP = Matrix::Identity;
		//	m_proj.Multiply(DecaleView, m_proj);
		//	m_VP = m_proj;

		//	m_DecaleVP[num] = m_VP;
		//	if (num == m_maxNum)
		//	{
		//		num = 0;
		//	}
		//	else
		//	{
		//		num++;
		//	}

		//}

		//並行投影行列を作成
		Matrix m_proj = Matrix::Identity;

		m_proj.MakeOrthoProjectionMatrix(m_SideLength, m_SideLength, 0.0f, 10.0f);
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
			//終点に方向に距離を掛けたもの足す
			EndPos += Direction * Distance;
			//終点をセット
			end.setValue(EndPos.x, EndPos.y, EndPos.z);

			//衝突検出
			SweepResult callback;
			callback.startPos = m_StartPos[i];
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

		m_STB.Update(m_DecaleVP.get());
	}
}