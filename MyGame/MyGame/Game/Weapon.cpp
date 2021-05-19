#include "stdafx.h"
#include "Weapon.h"

//衝突した時に呼ばれる関数オブジェクト
struct SweepResult : public btCollisionWorld::RayResultCallback
{
	bool isHit = false;						//衝突フラグ。
	Vector3 hitPos = Vector3::Zero;		//衝突点。
	Vector3 startPos = Vector3::Zero;		//レイの始点。

	//衝突したときに呼ばれるコールバック関数。
	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool /*normalInWorldSpace*/)
	{
		//ゴーストオブジェクト以外に衝突したとき
		if (rayResult.m_collisionObject->getInternalType() != btCollisionObject::CO_GHOST_OBJECT)
		{
			return 0.0f;
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
};

Weapon::~Weapon()
{
	//解放処理
	if (m_Model != nullptr)
	{
		DeleteGO(m_Model);
		m_Model = nullptr;
	}

}

void Weapon::Init(Skeleton* sk,bool IsDither)
{
	m_skeleton = sk;
	//モデルをNew
	m_Model = NewGO<prefab::ModelRender>(3);
	//ファイルパスをセット
	m_Model->SetTkmFilePath("Assets/modelData/AK_74M.tkm");
	//ディザリングを適応するかどうかのフラグ
	m_Model->SetDitherFlag(IsDither);
}
bool Weapon::Start()
{
	LeftHandBoneNo = m_skeleton->FindBoneID(L"mixamorig:LeftHand");

	return true;
}

void Weapon::AddDecale(const btVector3& start,const btVector3& end)
{
	g_graphicsEngine->GetDecale()->AddStartPos(start , end);
}

void Weapon::Update()
{
	//武器用の行列をボーンから取得
	m_weaponMat = m_skeleton->GetWeaponMatrix();
	//武器にワールド行列をセット
	m_Model->SetWorldMatrix(m_weaponMat);
	//直接行列をセットしているので行列の計算はしない
	m_Model->SetUpdateFlag(false);
}

void Weapon::shooting()
{
	//レイを作成
	btVector3 start, end;
	start.setZero();
	end.setZero();

	//カメラの位置
	Vector3 cameraPos = g_camera3D->GetPosition();
	//カメラの向き
	Vector3 Direction = g_camera3D->GetTarget() - g_camera3D->GetPosition();
	//方向を正規化
	Direction.Normalize();

	//始点をセット
	start.setValue(cameraPos.x, cameraPos.y, cameraPos.z);

	//終点となる位置を作成
	Vector3 EndPos = Vector3::Zero;
	//終点は始点となる位置に方向*距離を足したもの
	EndPos = cameraPos;
	//終点に方向に距離を掛けたもの足す
	EndPos += Direction * m_range;
	//終点をセット
	end.setValue(EndPos.x, EndPos.y, EndPos.z);



	//衝突検出
	SweepResult callback;
	//衝突検出
	g_engine->GetPhysicsWorld().RayTest(start, end, callback);

	//レイがゴーストオブジェクトに衝突しているとき
	if (callback.isHit)
	{
		callback.m_collisionObject->setActivationState(CollisionActivationState::Hit);
		int i = callback.m_collisionObject->getActivationState();
		return;
	}

	//衝突していなければデカールを追加
	AddDecale(start, end);
}