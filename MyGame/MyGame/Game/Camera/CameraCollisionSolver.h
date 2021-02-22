#pragma once
#include "SourceFile/Physics/SphereCollider.h"

//�J�����̃R���W��������
//�J������w�i�ɂ߂荞�܂������Ȃ��ꍇ�Ɏg���Ă�������
namespace Engine {
	class CameraCollisionSolver
	{
	public:
		//�R���X�g���N�^
		CameraCollisionSolver();
		//�f�X�g���N�^
		~CameraCollisionSolver();

		//������
		//radius		�X�t�B�A�R���C�_�[�̔��a
		void Init(float radius);

		//�R���W�����̉����̎��s
		//result		�R���W�����������s�������_�̍��W
		//position		�R���W�����������s���O�̎��_�̍��W
		//target		�J�����̒����_
		//�߂�l�̓R���W�����������s�����ꍇ��true���Ԃ��Ă���
		bool Execute(Vector3& result, const Vector3& position, const Vector3& target);
	private:
		SphereCollider m_collider;		//�R���C�_�[
		float m_radius = 0.0f;		//���a
		bool m_isInited = false;		//�������ς݂̃t���O
	};
}