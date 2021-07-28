#pragma once
#include "SourceFile/sound/SoundSource.h"
class SoundSource;
class Weapon:public IGameObject
{
	//衝突した時に呼ばれる関数オブジェクト
	struct SweepResult : public btCollisionWorld::RayResultCallback
	{
		void SetFireCharacter(int i)
		{
			FireCharacter = i;
		}
		int FireCharacter = enCollisionAttr_Num;
		bool isHit = false;						//衝突フラグ。
		//Vector3 hitPos = Vector3::Zero;		//衝突点。
		//Vector3 startPos = Vector3::Zero;		//レイの始点。
		btScalar ObjectNearDist = 10000.0;
		btScalar GhostDist = 10000.0;
		//衝突したときに呼ばれるコールバック関数。
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool /*normalInWorldSpace*/)
		{
			int UserIndex = rayResult.m_collisionObject->getUserIndex();

			if (UserIndex == FireCharacter)
			{
				return 0.0f;
			}
			//ゴーストオブジェクトとキャラコン以外に衝突したとき
			if (UserIndex == enCollisionAttr_StaticObject)
			{
				if (rayResult.m_hitFraction < ObjectNearDist)
				{
					ObjectNearDist = rayResult.m_hitFraction;
				}
				return 0.0f;
			}
			if (rayResult.m_collisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT)
			{
				if (rayResult.m_hitFraction < GhostDist)
				{
					GhostDist = rayResult.m_hitFraction;
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
			}
			return rayResult.m_hitFraction;
		}
	};
public:
	Weapon(){}
	~Weapon();
	void OnDestroy();
	bool Start();
	void Update();

	//初期化
	//sk		スケルトン
	//IsDither		ディザリングを適応するかどうかのフラグ
	void Init(Skeleton* sk,bool IsDither = false);

	//射撃
	//戻り値は射撃できたかどうか
	bool shooting();

	//射撃をやめた時の処理
	void Release()
	{
		m_IsFirstShoot = true;
	}
	bool IsAvailable()
	{
		if (m_Magazine > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void SetRay(const Vector3& startpos,const Vector3& dir)
	{
		m_RayStartPos = startpos;
		m_RayDirection = dir;
	}

	void StopFireSound(int i)
	{
		m_FireSound[i]->Stop();
	}

	void SetCharacter(int i)
	{
		Character = i;
	}
private:
	//デカールを追加
	//start		始点
	//end		終点
	void AddDecale(const btVector3& start, const btVector3& end);

private:
	Skeleton* m_skeleton = nullptr;		//スケルトン
	Vector3 m_weaponPos = Vector3::Zero;		//武器のポジション
	Quaternion m_weaponRot = Quaternion::Identity;		//武器の回転
	Matrix m_weaponMat = Matrix::Identity;		//武器の行列
	prefab::ModelRender* m_Model = nullptr;		//モデル
	int LeftHandBoneNo = -1;		//武器用のボーン番号
	const float m_range = 10000.0f;		//射程
	const int rate = 10;
	float time = 0.0f;
	Vector3 m_RayStartPos = Vector3::Zero;
	Vector3 m_RayDirection = Vector3::Zero;
	SoundSource* m_FireSound[FireSoundNum_Rifle] = { nullptr };
	SoundSource* m_OutOfAmmoSound = nullptr;
	int Character = enCollisionAttr_Num;
	const float m_FireCurveDistance = 3000.0f;
	const float m_OutOfAmmoCurveDistance = 500.0f;
	int m_Magazine = 30;
	bool m_IsFirstShoot = true;
};

