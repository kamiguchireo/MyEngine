#include "stdafx.h"
#include "RigidBody.h"
#include "ICollider.h"

namespace Engine {
	RigidBody::~RigidBody()
	{
		Release();
	}
	void RigidBody::Release()
	{

	}

	void RigidBody::Create(RigidBodyInfo& rbInfo)
	{
		Release();
		btTransform transform;
		//初期化
		transform.setIdentity();
		//ポジションをセット
		transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
		//回転をセット
		transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w));
		m_myMotionState = std::make_unique<btDefaultMotionState>();
		m_myMotionState->setWorldTransform(transform);
		btVector3 btLocalInteria;
		rbInfo.localInteria.CopyTo(btLocalInteria);
		btRigidBody::btRigidBodyConstructionInfo btRbInfo(rbInfo.mass, m_myMotionState.get(), rbInfo.collider->GetBody(), btLocalInteria);
		//剛体を作成
		m_rigidBody = std::make_unique<btRigidBody>(btRbInfo);
	}
}