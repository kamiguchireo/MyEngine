#pragma once

namespace Engine {

	class ICollider;

	//���̂̏��
	struct RigidBodyInfo {
		RigidBodyInfo() :
			collider(NULL),
			mass(0.0f)
		{
			pos = Vector3::Zero;
			rot = Quaternion::Identity;
			localInteria = Vector3::Zero;
		}
		Vector3 pos;		//���W
		Quaternion rot;		//��]
		Vector3 localInteria;		//�����e���\��
		ICollider* collider;		//�R���C�_�[
		float mass;		//����
	};

	//���̃N���X
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

		//�������[���h�ɓo�^���Ă���t���O�𗧂Ă�
		void SetMarkAddPhysicsWorld()
		{
			m_isAddPhysicsWorld = true;
		}
		//�������[���h�ɓo�^���Ă���t���O���O��
		void SetUnmarkAddPhysicsWorld()
		{
			m_isAddPhysicsWorld = false;
		}
		//�������[���h�ɒǉ�����Ă��邩�ǂ���
		bool IsAddPhysicsWorld()const
		{
			return m_isAddPhysicsWorld;
		}
		//�����I�u�W�F�N�g�̍��W�Ɖ�]���擾
		//pos		���W
		//rot		��]
		void GetPositionAndRotateion(Vector3& pos, Quaternion& rot)
		{
			btTransform trans;
			m_myMotionState->getWorldTransform(trans);
			pos.Set(trans.getOrigin());
			rot.Set(trans.getRotation());
		}
		//�����I�u�W�F�N�g�̍��W�Ɖ�]��ݒ�
		//pos		���W
		//rot		��]
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
		//�͂�������
		//force		��
		//relPos		�͂���������W
		void AddForce(const Vector3& force, const Vector3& relPos)
		{
			btVector3 btForce;
			btVector3 btRelPos;
			force.CopyTo(btForce);
			relPos.CopyTo(btRelPos);
			m_rigidBody->applyForce(btForce, btRelPos);
		}
	private:
		std::unique_ptr<btRigidBody> m_rigidBody;		//����
		std::unique_ptr<btDefaultMotionState> m_myMotionState;		//���[�V�����X�e�[�g
		bool m_isAddPhysicsWorld = false;		//�������[���h�ɒǉ�����Ă��邩
	};

}