#include "stdafx.h"
#include "Decale.h"

namespace Engine {
	
	//�Փ˂������ɌĂ΂��֐��I�u�W�F�N�g
	struct SweepResult : public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;						//�Փ˃t���O�B
		Vector3 hitPos = Vector3::Zero;		//�Փ˓_�B
		Vector3 startPos = Vector3::Zero;		//���C�̎n�_�B
		float dist = FLT_MAX;					//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
		Vector3 hitNormal = Vector3::Zero;	//�Փ˓_�̖@���B

		//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
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
			//������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�B
			float angle = fabsf(acosf(hitNormalTmp.Dot(Vector3::Up)));
		
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

	void Decale::CalcVP(const Vector3& pos, const Vector3& right, const Vector3& dir)
	{
		//���s���e�s����쐬
		Matrix m_proj = Matrix::Identity;

		m_proj.MakeOrthoProjectionMatrix(m_SideLength, m_SideLength, 0.0f, 10.0f);
		//���C���쐬
		btVector3 start, end;
		start.setZero();
		end.setZero();
	
		//�n�_���Z�b�g
		start.setValue(pos.x, pos.y, pos.z);
		//�I�_�ƂȂ�ʒu���쐬
		Vector3 EndPos = Vector3::Zero;
		//�I�_�͎n�_�ƂȂ�ʒu�ɕ���*�����𑫂�������
		EndPos = pos;
		Vector3 Direction = Vector3::Zero;
		Direction = dir;
		//�����𐳋K��
		Direction.Normalize();
		//�I�_�ɕ����ɋ������|�������̑���
		EndPos += Direction * Distance;
		//�I�_���Z�b�g
		end.setValue(EndPos.x, EndPos.y, EndPos.z);

		//�Փˌ��o
		SweepResult callback;
		callback.startPos = pos;
		//�Փˌ��o
		g_engine->GetPhysicsWorld().RayTest(start, end, callback);
		callback.hasHit();
		if (callback.isHit)
		{
			btVector3 hitPosTmp = start + (end - start) * callback.m_closestHitFraction;
			//�����I�u�W�F�N�g�ƏՓ˂���
			Vector3 hitPos;
			hitPos.Set(hitPosTmp);
			//�J������ݒu���邽�߂ɏ����߂Â���
			hitPos -= Direction * 1.0f;
			//�J�����s�����邽�߂Ƀ^�[�Q�b�g�|�W�V�������쐬
			Vector3 targetPos = hitPos;
			//�^�[�Q�b�g�͏�������
			targetPos += Direction * 1.0f;
			//�J�����s����쐬
			Matrix m_view = Matrix::Identity;
			//�J�����̑O����
			Vector3 cameraForward = Vector3::Front;
			cameraForward = g_camera3D->GetForward();
			//�J�����̉E����
			Vector3 ViewRight = Vector3::Right;
			ViewRight.Cross(Direction, cameraForward);
			//���K��
			ViewRight.Normalize();
			//�J�����̏����
			Vector3 CameraUpAxis = Vector3::Up;
			CameraUpAxis.Cross(ViewRight, Direction);
			//���K��
			CameraUpAxis.Normalize();

			//�J�����s����쐬
			m_view.MakeLookAt(hitPos, targetPos, CameraUpAxis);

			Matrix m_VP = Matrix::Identity;
			m_proj.Multiply(m_view, m_proj);
			m_VP = m_proj;
			m_DecaleVP[num] = m_VP;
			if (num == m_maxNum)
			{
				num = 0;
			}
			else
			{
				num++;
			}
		}
		
	}
}