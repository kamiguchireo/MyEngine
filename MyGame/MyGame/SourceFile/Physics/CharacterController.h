#pragma once
#include "CapsuleCollider.h"

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

		}

		//������
		//radius		�J�v�Z���R���C�_�[�̔��a
		//height		�J�v�Z���R���C�_�[�̍���
		//position		�����ʒu
		void Init(float radius, float height, const Vector3& position);

	private:
		bool m_isInited = false;		//�������t���O
		Vector3 m_position = Vector3::Zero;		//���W
		bool m_isJump = false;		//�W�����v�t���O
		bool m_isOnGround = true;		//�n�ʂ̏�ɂ���
		CapsuleCollider m_collider;		//�R���C�_�[
		float m_radius = 0.0f;		//�J�v�Z���R���C�_�[�̔��a
		float m_height = 0.0f;		//�J�v�Z���R���C�_�[�̍���

	};
}