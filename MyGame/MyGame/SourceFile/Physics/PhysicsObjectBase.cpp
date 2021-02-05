#include "stdafx.h"
#include "PhysicsObjectBase.h"
#include "MeshCollider.h"

namespace Engine {
	void PhysicsObjectBase::CreateMesh(Vector3 pos, Quaternion rot, const Model& skinModel)
	{
		Release();
		auto meshCollider = std::make_unique<MeshCollider>();
		meshCollider->CreateFromModel(skinModel, nullptr);
		m_collider = move(meshCollider);
		CreateCommon(pos, rot);
	}
}