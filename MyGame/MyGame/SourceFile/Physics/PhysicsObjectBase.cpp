#include "stdafx.h"
#include "PhysicsObjectBase.h"
#include "MeshCollider.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "SphereCollider.h"
#include "CylinderCollider.h"

namespace Engine {

	void PhysicsObjectBase::CreateBox(Vector3 pos, Quaternion rot, Vector3 size)
	{
		Release();
		auto boxCollider = std::make_unique<BoxCollider>();
		boxCollider->Create(size);
		m_collider = move(boxCollider);
		CreateCommon(pos, rot);
	}

	void PhysicsObjectBase::CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height)
	{
		Release();
		auto capsuleCollider = std::make_unique<CapsuleCollider>();
		capsuleCollider->Create(radius, height);
		m_collider = move(capsuleCollider);
		CreateCommon(pos, rot);
	}

	void PhysicsObjectBase::CreateSphere(Vector3 pos, Quaternion rot, float radius)
	{
		Release();
		auto sphereCollider = std::make_unique<SphereCollider>();
		sphereCollider->Create(radius);
		m_collider = move(sphereCollider);
		CreateCommon(pos, rot);
	}

	void PhysicsObjectBase::CreateCylinder(Vector3 pos, Quaternion rot, Vector3 size)
	{
		Release();
		auto cylinderCollider = std::make_unique<CylinderCollider>();
		cylinderCollider->Create(size);
		m_collider = move(cylinderCollider);
		CreateCommon(pos, rot);
	}

	void PhysicsObjectBase::CreateMesh(Vector3 pos, Quaternion rot, const Model& skinModel)
	{
		Release();
		auto meshCollider = std::make_unique<MeshCollider>();
		meshCollider->CreateFromModel(skinModel, nullptr);
		m_collider = move(meshCollider);
		CreateCommon(pos, rot);
	}
}