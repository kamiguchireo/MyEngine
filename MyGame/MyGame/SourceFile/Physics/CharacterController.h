#pragma once

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
	};
}