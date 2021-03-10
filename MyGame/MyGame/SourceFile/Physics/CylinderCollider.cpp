#include "stdafx.h"
#include "CylinderCollider.h"

namespace Engine {
	CylinderCollider::CylinderCollider()
	{

	}

	CylinderCollider::~CylinderCollider()
	{

	}

	void CylinderCollider::Create(Vector3& vec)
	{
		shape = new btCylinderShape(btVector3(vec.x,vec.y,vec.z));
	}
}