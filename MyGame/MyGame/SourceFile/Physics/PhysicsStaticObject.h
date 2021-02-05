#pragma once
#include "MeshCollider.h"
#include "RigidBody.h"
#include "PhysicsObjectBase.h"

namespace Engine {
	class PhysicsStaticObject : public PhysicsObjectBase
	{
	public:
		~PhysicsStaticObject()
		{
			Release();
		}

		//解放処理
		void Release()override final;

		//座標と回転を設定
		void SetPositionAndRotation(const Vector3& pos, const Quaternion& rot)
		{
			m_rigidBody.SetPositionAndRotation(pos, rot);
		}

		RigidBody& GetRigidBody()
		{
			return m_rigidBody;
		}

	private:
		//性的物理オブジェクト作成処理の共通処理
		void CreateCommon(Vector3 pos, Quaternion rot)override final;

	private:
		RigidBody m_rigidBody;		//剛体
	};
}