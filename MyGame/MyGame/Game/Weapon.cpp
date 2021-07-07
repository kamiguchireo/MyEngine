#include "stdafx.h"
#include "Weapon.h"



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
	time += g_gameTime.GetFrameDeltaTime();
	//1秒間にrateの数だけ撃てる
	if (time >= 1.0f / rate)
	{
		//レイを作成
		btVector3 start, end;
		start.setZero();
		end.setZero();

		//始点をセット
		start.setValue(m_RayStartPos.x, m_RayStartPos.y, m_RayStartPos.z);

		//終点となる位置を作成
		Vector3 EndPos = Vector3::Zero;
		//終点は始点となる位置に方向*距離を足したもの
		EndPos = m_RayStartPos;
		//終点に方向に距離を掛けたもの足す
		EndPos += m_RayDirection * m_range;
		//終点をセット
		end.setValue(EndPos.x, EndPos.y, EndPos.z);

		//衝突検出
		SweepResult callback;
		//衝突検出
		g_engine->GetPhysicsWorld().RayTest(start, end, callback);

		//レイがゴーストオブジェクトに衝突しているとき
		if (callback.isHit)
		{
			//ゴーストオブジェクトより手前にオブジェクトが何もないとき
			if (callback.GhostDist < callback.ObjectNearDist)
			{
				//コリジョンのステートをヒットにする
				callback.m_collisionObject->setActivationState(CollisionActivationState::Hit);
				return;
			}
		}
		else
		{
			//衝突していなければデカールを追加
			AddDecale(start, end);
			time = 0.0f;
		}
	}
	else
	{
		return;
	}
}