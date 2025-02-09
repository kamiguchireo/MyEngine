#pragma once
#include "PhysicsObjectBase.h"

namespace Engine {
	//ゴーストオブジェクト
	//剛体はすり抜ける当たり判定のオブジェクト
	class PhysicsGhostObject :public PhysicsObjectBase
	{
	public:
		~PhysicsGhostObject()
		{
			Release();
		}

		//解放処理
		void Release() override final;

		//引数で渡されたゴーストオブジェクトが自分自身かどうか判定
		bool IsSelf(const btCollisionObject& ghost)const
		{
			return &ghost == &m_ghostObject;
		}

		//座標を設定
		void SetPosition(const Vector3& pos)
		{
			auto& btTrans = m_ghostObject.getWorldTransform();
			btVector3 btPos;
			pos.CopyTo(btPos);
			btTrans.setOrigin(btPos);
		}

		//回転を設定
		void SetRotation(const Quaternion& rot)
		{
			auto& btTrans = m_ghostObject.getWorldTransform();
			btQuaternion btRot;
			rot.CopyTo(btRot);
			btTrans.setRotation(btRot);
		}

		//ゴーストオブジェクトを移動
		void UpdateWorldMatrix(const Vector3& pos,const Quaternion& rot);

		//アクティベーションステートをゲット
		int GetActivationState()
		{
			return m_ghostObject.getActivationState();
		}
		//アクティベーションステートをセット
		void SetActivationState(int i)
		{
			m_ghostObject.setActivationState(i);
		}

		void SetUserIndex(int i)
		{
			m_ghostObject.setUserIndex(i);
		}
	private:
		//ゴースト作成処理の共通処理
		void CreateCommon(Vector3 pos, Quaternion rot)override;
	private:
		bool m_isRegistPhysicsWorld = false;		//物理ワールドに登録しているかどうか
		btGhostObject m_ghostObject;		//ゴーストオブジェクト
	};
}