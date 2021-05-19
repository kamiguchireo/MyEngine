#include "stdafx.h"
#include "Decale.h"

namespace Engine {
	
	//�Փ˂������ɌĂ΂��֐��I�u�W�F�N�g
	struct SweepResult : public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;						//�Փ˃t���O�B
		Vector3 hitNormal = Vector3::Zero;	//�Փ˓_�̖@���B

		//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool /*normalInWorldSpace*/)
		{
			//�������n�ʂɏՓ˂����Ƃ�
			if (rayResult.m_collisionObject->getUserIndex() == enCollisionAttr_Character
				||rayResult.m_collisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT)
			{
				return 0.0f;
			}
			//�Փ˓_�̖@��
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(rayResult.m_hitNormalLocal);
		
			isHit = true;
				
			if (rayResult.m_hitFraction < m_closestHitFraction)
			{
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
				hitNormal = hitNormalTmp;
				m_closestHitFraction = rayResult.m_hitFraction;
			}
			
			return rayResult.m_hitFraction;
		}
	};

	Decale::Decale()
	{

	}

	Decale::~Decale()
	{

	}

	void Decale::Init()
	{
		//���j�[�N�|�C���^���쐬
		m_DecaleVP.reset(new Matrix[m_maxNum]);
		//�X�g���N�`���[�o�b�t�@��������
		m_STB.Init(
			sizeof(Matrix),
			m_maxNum,
			m_DecaleVP.get()
		);

		m_DecaleTex.InitFromDDSFile(L"Assets/Image/BulletDecale.dds");
		for (int i = 0; i < m_maxNum; i++)
		{
			m_DecaleVP[i] =
			{
			0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f
			};
		}
	}
	void Decale::Update()
	{
		m_STB.Update(m_DecaleVP.get());
	}

	void Decale::CalcVP(const btVector3& start, const btVector3& end)
	{
		//���s���e�s����쐬
		Matrix m_proj = Matrix::Identity;

		m_proj.MakeOrthoProjectionMatrix(m_SideLength, m_SideLength, 0.0f, 10.0f);

		//�Փˌ��o
		SweepResult callback;
		//�Փˌ��o
		g_engine->GetPhysicsWorld().RayTest(start, end, callback);

		//���C���Փ˂��Ă���Ƃ�
		if (callback.isHit)
		{
			//���������ʒu
			btVector3 hitPosTmp = start + (end - start) * callback.m_closestHitFraction;
			//���������ʒu�̖@��
			Vector3 hitNormal = callback.hitNormal;

			//�J�����̎��_
			Vector3 CameraPos = Vector3::Zero;
			//�J�����̒����_
			Vector3 CameraTarget = Vector3::Zero;

			//�Z�b�g
			CameraPos.Set(hitPosTmp);
			CameraTarget.Set(hitPosTmp);

			//�J�����̎��_�Ȃ̂Ŗ@�������Ɉړ�����
			CameraPos += hitNormal;
			//�J�����̒����_�Ȃ̂Ŗ@���̋t�����Ɉړ�����
			CameraTarget -= hitNormal;

			//�J�����s����쐬
			Matrix m_view = Matrix::Identity;

			//���_���璍���_�ւ̃x�N�g��
			Vector3 PosToTarget = CameraTarget - CameraPos;
			//���K��
			PosToTarget.Normalize();

			//�J�����̌������قƂ�ǐ^�ォ�^���̎�
			if (PosToTarget.y >= 0.99 || PosToTarget.y <= -0.99)
			{
				//{1.0f,0.0f,0.0f}��������Ƃ��ăJ�����s����쐬
				m_view.MakeLookAt(CameraPos, CameraTarget, Vector3::Right);
			}
			else
			{
				//����ȊO�̎�
				//{0.0f,1.0f,0.0f}��������Ƃ��ăJ�����s����쐬
				m_view.MakeLookAt(CameraPos, CameraTarget, Vector3::Up);
			}
			//�r���[�v���W�F�s��
			Matrix m_VP = Matrix::Identity;
			m_proj.Multiply(m_view, m_proj);
			m_VP = m_proj;
			m_DecaleVP[num] = m_VP;
			//���݂̃f�J�[���̔ԍ��𑝂₷
			num++;
			//�ő�l�ɂȂ��Ă�����0�ɖ߂�
			num %= m_maxNum;
		}
		
	}
}