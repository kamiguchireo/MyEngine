#pragma once
#include "CapsuleCollider.h"
#include "RigidBody.h"

//�L�����N�^�[�R���g���[���[
//�L�����N�^�[�Ɣw�i�̏Փˉ������s��
namespace Engine {
	class CharacterController
	{
	public:
		CharacterController()
		{

		}
		~CharacterController()
		{
			RemoveRigidBody();
		}

		//������
		//radius		�J�v�Z���R���C�_�[�̔��a
		//height		�J�v�Z���R���C�_�[�̍���
		//position		�����ʒu
		void Init(float radius, float height, const Vector3& position);

		//���s
		//moveSpeed		�ړ����x
		//deltaTime		�o�ߎ��ԁB�P�ʂ͕b�B�f�t�H���g�ł�1�t���[���̌o�ߎ��Ԃ��n����Ă���
		//return		�ړ���̃L�����N�^�[�̍��W
		const Vector3& Execute(Vector3& moveSpeed);

		//���̂��t�B�W�b�N�X���[���h����폜
		void RemoveRigidBody();

		RigidBody* GetRigidBody()
		{
			return &m_rigidBody;
		}

		//�n�ʂ̏�ɂ��邩�ǂ���
		bool IsOnGround()const
		{
			return m_isOnGround;
		}
	private:
		bool m_isInited = false;		//�������t���O
		Vector3 m_position = Vector3::Zero;		//���W
		bool m_isJump = false;		//�W�����v�t���O
		bool m_isOnGround = true;		//�n�ʂ̏�ɂ���
		CapsuleCollider m_collider;		//�R���C�_�[
		float m_radius = 0.0f;		//�J�v�Z���R���C�_�[�̔��a
		float m_height = 0.0f;		//�J�v�Z���R���C�_�[�̍���
		RigidBody m_rigidBody;		//����
		const float OverStep = 0.25f;
	};
}