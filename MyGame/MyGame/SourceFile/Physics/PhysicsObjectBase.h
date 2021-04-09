#pragma once
#include "SourceFile/graphic/ModelRender.h"
#include "ICollider.h"

namespace Engine {
	//�����I�u�W�F�N�g�̃x�[�X�N���X
	class PhysicsObjectBase
	{
	public:
		//�S�[�X�g�I�u�W�F�N�g�����
		virtual void Release() = 0;

	private:
		//�ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ���
		virtual void CreateCommon(Vector3 pos, Quaternion rot) = 0;

	public:
		PhysicsObjectBase()
		{

		}
		~PhysicsObjectBase()
		{

		}

		//�{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬
		//pos		���W
		//rot		��]
		//size		�T�C�Y
		void CreateBox(Vector3 pos, Quaternion rot, Vector3 size);

		//�J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬
		// pos		���W
		// rot		��]
		// radius		�J�v�Z���̔��a
		// height		�J�v�Z���̍���
		void CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height);

		//���̌`��̃S�[�X�g�I�u�W�F�N�g���쐬
		//pos		���W
		//rot		��]
		//radius		���̂̔��a
		void CreateSphere(Vector3 pos, Quaternion rot, float radius);

		//�~���`��̃S�[�X�g�I�u�W�F�N�g���쐬
		//pos		���W
		//rot		��]
		//size		�~���̃T�C�Y
		void CreateCylinder(Vector3 pos, Quaternion rot, Vector3 size);
		//���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬
		//pos		���W
		//rot		��]
		//skinModel	���f��
		void CreateMesh(Vector3 pos, Quaternion rot, const Model& skinModel);
	protected:
		std::unique_ptr<ICollider> m_collider;		//�R���C�_�[
	};
}