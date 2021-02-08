#pragma once
#include "SourceFile/graphic/ModelRender.h"

namespace Engine {
	//�����I�u�W�F�N�g�̃x�[�X�N���X
	class PhysicsObjectBase
	{
	public:
		//�S�[�X�g�I�u�W�F�N�g�����
		virtual void Release() = 0;

	private:
		//���I�����I�u�W�F�N�g�쐬�����̋��ʏ���
		virtual void CreateCommon(Vector3 pos, Quaternion rot) = 0;

	public:
		PhysicsObjectBase()
		{

		}
		~PhysicsObjectBase()
		{

		}

		//���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬
		//pos		���W
		//rot		��]
		//skinModel	���f��
		void CreateMesh(Vector3 pos, Quaternion rot, const Model& skinModel);
	protected:
		std::unique_ptr<ICollider> m_collider;		//�R���C�_�[
	};
}