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

		//�S�[�X�g�I�u�W�F�N�g���ړ�
		void UpdateWorldMatrix(const Vector3& pos,const Quaternion& rot);

		//�A�N�e�B�x�[�V�����X�e�[�g���Q�b�g
		int GetActivationState()
		{
			return m_ghostObject.getActivationState();
		}
		//�A�N�e�B�x�[�V�����X�e�[�g���Z�b�g
		void SetActivationState(int i)
		{
			m_ghostObject.setActivationState(i);
		}
	private:
		//�S�[�X�g�쐬�����̋��ʏ���
		void CreateCommon(Vector3 pos, Quaternion rot)override;
	private:
		bool m_isRegistPhysicsWorld = false;		//�������[���h�ɓo�^���Ă��邩�ǂ���
		btGhostObject m_ghostObject;		//�S�[�X�g�I�u�W�F�N�g
	};
}