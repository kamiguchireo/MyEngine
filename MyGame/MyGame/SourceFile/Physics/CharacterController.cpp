#include "stdafx.h"
#include "CharacterController.h"

namespace Engine {
	namespace {
		//衝突したときに呼ばれる関数オブジェクト(地面用)
		struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;		//衝突フラグ
			Vector3 hitPos = Vector3(0.0f, -FLT_MAX, 0.0f);		//衝突点
			Vector3 startPos = Vector3::Zero;		//レイの始点
			Vector3 hitNormal = Vector3::Zero;		//衝突点の法線
			btCollisionObject* me = nullptr;		//自分自身。自分自身との衝突を回避するためのメンバ
			float dist = FLT_MAX;		//衝突点までの距離。一番近い衝突点を求めるため。

			//衝突したときに呼ばれるコールバック関数
			virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool /*normalInWorldSpace*/)
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
			virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool /*normalInWorldSpace*/)
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
	}

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
		//属性をキャラコンにする
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
		//フィジックスワールドに登録
		g_engine->GetPhysicsWorld() .AddRigidBody(m_rigidBody);
		m_isInited = true;
	}

	const Vector3& CharacterController::Execute(Vector3& moveSpeed)
	{
		if (moveSpeed.LengthSq() <= 0.0001f)
		{
			//移動速度が小さすぎるので0とみなす
			return m_position;
		}
		//初期化されていないキャラクターコントローラーが使われたとき
		if (m_isInited == false)
		{
			//処理を停止
			std::abort();
		}

		if (moveSpeed.y > 0.0f)
		{
			//ジャンプ中にする
			m_isJump = true;
			m_isOnGround = false;
		}
		//次の移動先となる座標を計算する
		Vector3 nextPosition = m_position;
		//速度からこのフレームでの移動量を求める。
		//オイラー積分
		Vector3 addPos = moveSpeed;
		nextPosition.Add(addPos);
		Vector3 originalXZDir = addPos;
		originalXZDir.y = 0.0f;
		originalXZDir.Normalize();
		//XZ平面での衝突検出と衝突解決を行う
		int loopCount = 0;
		while (true)
		{
			//現在の座標から次の移動先へ向かうベクトルを求める
			Vector3 AddPos;
			//減算
			AddPos.Subtract(nextPosition, m_position);
			Vector3 addPosXZ = AddPos;
			addPosXZ.y = 0.0f;
			if (addPosXZ.Length() < FLT_EPSILON)
			{
				//XZ平面で動きがないので調べなくてよい
				//FLT_EPSILONはとても小さい値のこと
				break;
			}
			Vector3 posTmp = m_position;
			//カプセルコライダーの中心座標 + 高さ*0.35fの座標をposTmpに求める
			posTmp.y += m_height * 0.5f + m_radius + m_height * OverStep;
			//レイを作成
			btTransform start, end;
			//始点
			start.setIdentity();
			//終点
			end.setIdentity();
			//始点はカプセルコライダーの中心座標 + 0.2fの座標をposTmpに求める
			start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
			//終点は次の移動先。XZ平面での衝突を調べるので、yはposTmp.yを設定する
			end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

			SweepResultWall callback;
			callback.me = m_rigidBody.GetBody();
			callback.startPos = posTmp;
			//衝突検出
			g_engine->GetPhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);

			//当たったとき
			if (callback.isHit)
			{
				//壁
				Vector3 vT0, vT1;
				//XZ平面上での異動後の座標をvT0に、交点の座標をvT1に設定する
				vT0.Set(nextPosition.x, 0.0f, nextPosition.z);
				vT1.Set(callback.hitPos.x, 0.0f, callback.hitPos.z);
				//めり込みが発生している移動ベクトルを求める
				Vector3 vMerikomi;
				vMerikomi.Subtract(vT0, vT1);
				//XZ平面での衝突した壁の法線を求める
				Vector3 hitNormalXZ = callback.hitNormal;
				hitNormalXZ.y = 0.0f;
				hitNormalXZ.Normalize();
				//めり込みベクトルを壁の法線に射影する
				float fT0 = hitNormalXZ.Dot(vMerikomi);
				//押し返すベクトルを求める
				//押し返すベクトルは壁の法線に射影されためり込みベクトル + 半径
				Vector3 vOffset;
				vOffset = hitNormalXZ;
				vOffset.Scale(-fT0 + m_radius);
				nextPosition.Add(vOffset);
				Vector3 currentDir;
				currentDir.Subtract(nextPosition, m_position);
				currentDir.y = 0.0f;
				currentDir.Normalize();
				if (currentDir.Dot(originalXZDir) < 0.0f)
				{
					//移動先が逆向きになったら移動をキャンセル
					nextPosition.x = m_position.x;
					nextPosition.z = m_position.z;
					break;
				}
			}
			else
			{
				//どこにも当たらなかったとき
				break;
			}
			loopCount++;
			if (loopCount == 5)
			{
				break;
			}
		}
		//XZの移動は確定
		m_position.x = nextPosition.x;
		m_position.z = nextPosition.z;
		
		//下方向を調べる
		Vector3 AddPos;
		AddPos.Subtract(nextPosition, m_position);
		m_position = nextPosition;		//移動の仮確定
		//レイを作成
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//始点はカプセルコライダーの中心
		start.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
		//終点は地面上にいない場合は1m下を見る
		//地面上にいなくいてジャンプで上昇中の場合は上昇量の0.01倍下を見る
		//地面上にいなくて降下中の場合はそのまま落下先を調べる
		Vector3 endPos;
		endPos.Set(start.getOrigin());
		//空中にいるとき
		//if (m_isOnGround == false)
		//{
		//	//上昇中
		//	if (AddPos.y > 0.0f)
		//	{
		//		//上昇中でもXZに移動した結果めり込んでいる可能性があるので下を調べる
		//		endPos.y -= AddPos.y;
		//	}
		//	else
		//	{
		//		//落下しているとき
		//		endPos.y += AddPos.y;
		//	}
		//}
		//else
		//{
			//地面上にいない場合は1m下を見る
			endPos.y -= 1.0f;
		//}
		end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
		SweepResultGround callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos.Set(start.getOrigin());
		//衝突検出
		if (fabsf(endPos.y - callback.startPos.y) > FLT_EPSILON)
		{
			g_engine->GetPhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
			if (callback.isHit)
			{
				//当たった
				moveSpeed.y = 0.0f;
				m_isJump = false;
				m_isOnGround = true;
				nextPosition.y = callback.hitPos.y;
			}
			else
			{
				//地面上にいない
				m_isOnGround = false;
			}
		}
		//移動確定
		m_position = nextPosition;
		btRigidBody* btBody = m_rigidBody.GetBody();
		//剛体を動かす
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		//剛体の位置を更新
		trans.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
		return m_position;
	}

	//死亡したことを通知
	void CharacterController::RemoveRigidBody()
	{
		g_engine->GetPhysicsWorld().RemoveRigidBody(m_rigidBody);
	}
}
