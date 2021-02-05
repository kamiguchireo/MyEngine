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

		//�������
		void Release()override final;

		//���W�Ɖ�]��ݒ�
		void SetPositionAndRotation(const Vector3& pos, const Quaternion& rot)
		{
			m_rigidBody.SetPositionAndRotation(pos, rot);
		}

		RigidBody& GetRigidBody()
		{
			return m_rigidBody;
		}

	private:
		//���I�����I�u�W�F�N�g�쐬�����̋��ʏ���
		void CreateCommon(Vector3 pos, Quaternion rot)override final;

	private:
		RigidBody m_rigidBody;		//����
	};
}