#pragma once

namespace Engine {

	class ICollider;

	//剛体の情報
	struct RigidBodyInfo {
		RigidBodyInfo() :
			collider(NULL),
			mass(0.0f)
		{
			pos = Vector3::Zero;
			rot = Quaternion::Identity;
			localInteria = Vector3::Zero;
		}
		Vector3 pos;		//座標
		Quaternion rot;		//回転
		Vector3 localInteria;		//慣性テンソル
		ICollider* collider;		//コライダー
		float mass;		//質量
	};

	//剛体クラス
	class RigidBody
	{
	public:
		~RigidBody();
		void Release();
		void Create(RigidBodyInfo& rbInfo);
		btRigidBody* GetBody()
		{
			return m_rigidBody.get();
		}

		//物理ワールドに登録しているフラグを立てる
		void SetMarkAddPhysicsWorld()
		{
			m_isAddPhysicsWorld = true;
		}
		//物理ワールドに登録しているフラグを外す
		void SetUnmarkAddPhysicsWorld()
		{
			m_isAddPhysicsWorld = false;
		}
		//物理ワールドに追加されているかどうか
		bool IsAddPhysicsWorld()const
		{
			return m_isAddPhysicsWorld;
		}
		//物理オブジェクトの座標と回転を取得
		//pos		座標
		//rot		回転
		void GetPositionAndRotateion(Vector3& pos, Quaternion& rot)
		{
			btTransform trans;
			m_myMotionState->getWorldTransform(trans);
			pos.Set(trans.getOrigin());
			rot.Set(trans.getRotation());
		}
		//物理オブジェクトの座標と回転を設定
		//pos		座標
		//rot		回転
		void SetPositionAndRotation(const Vector3& pos, const Quaternion& rot)
		{
			btTransform trans;
			btVector3 btPos;
			pos.CopyTo(btPos);
			trans.setOrigin(btPos);
			btQuaternion btRot;
			rot.CopyTo(btRot);
			trans.setRotation(btRot);
			m_rigidBody->setWorldTransform(trans);
		}
		//力を加える
		//force		力
		//relPos		力を加える座標
		void AddForce(const Vector3& force, const Vector3& relPos)
		{
			btVector3 btForce;
			btVector3 btRelPos;
			force.CopyTo(btForce);
			relPos.CopyTo(btRelPos);
			m_rigidBody->applyForce(btForce, btRelPos);
		}
	private:
		std::unique_ptr<btRigidBody> m_rigidBody;		//剛体
		std::unique_ptr<btDefaultMotionState> m_myMotionState;		//モーションステート
		bool m_isAddPhysicsWorld = false;		//物理ワールドに追加されているか
	};

}