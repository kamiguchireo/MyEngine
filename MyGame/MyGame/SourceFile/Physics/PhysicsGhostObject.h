#pragma once
#include "PhysicsObjectBase.h"

namespace Engine {
	//�S�[�X�g�I�u�W�F�N�g
	//���̂͂��蔲���铖���蔻��̃I�u�W�F�N�g
	class PhysicsGhostObject :public PhysicsObjectBase
	{
	public:
		~PhysicsGhostObject()
		{
			Release();
		}

		//�������
		void Release() override final;

		//�����œn���ꂽ�S�[�X�g�I�u�W�F�N�g���������g���ǂ�������
		bool IsSelf(const btCollisionObject& ghost)const
		{
			return &ghost == &m_ghostObject;
		}

		//���W��ݒ�
		void SetPosition(const Vector3& pos)
		{
			auto& btTrans = m_ghostObject.getWorldTransform();
			btVector3 btPos;
			pos.CopyTo(btPos);
			btTrans.setOrigin(btPos);
		}

		//��]��ݒ�
		void SetRotation(const Quaternion& rot)
		{
			auto& btTrans = m_ghostObject.getWorldTransform();
			btQuaternion btRot;
			rot.CopyTo(btRot);
			btTrans.setRotation(btRot);
		}

	private:
		//�S�[�X�g�쐬�����̋��ʏ���
		void CreateCommon(Vector3 pos, Quaternion rot)override;
	private:
		bool m_isRegistPhysicsWorld = false;		//�������[���h�ɓo�^���Ă��邩�ǂ���
		btGhostObject m_ghostObject;		//�S�[�X�g�I�u�W�F�N�g
	};
}