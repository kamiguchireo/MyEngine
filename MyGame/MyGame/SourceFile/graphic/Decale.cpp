#include "stdafx.h"
#include "Decale.h"

namespace Engine {
	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
	struct SweepResultGround : public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;		//�Փ˃t���O
		Vector3 hitPos = Vector3(0.0f, -FLT_MAX, 0.0f);		//�Փ˓_
		Vector3 startPos = Vector3::Zero;		//���C�̎n�_
		Vector3 hitNormal = Vector3::Zero;		//�Փ˓_�̖@��
		float dist = FLT_MAX;		//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁B
		
		//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐�
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
		{
			//�����ɏՓ˂����Ƃ�
			if (rayResult.m_collisionObject->getUserIndex() == enCollisionAttr_Character
				||rayResult.m_collisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT
				)
			{
				return 0.0f;
			}

			//�Փ˓_�̖@��
			Vector3 hitNormalTmp = *(Vector3*)&rayResult.m_hitNormalLocal;
			//������Ɩ@���̂Ȃ��p�����߂�
			float angle = hitNormalTmp.Dot(Vector3::Up);
			angle = fabsf(acosf(angle));
			//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ�
			if (angle < Math::PI * 0.3f)
			{
				//�Փ˂��Ă���
				isHit = true;
				Vector3 hitPosTmp = *(Vector3*)&rayResult.m_hitNormalLocal;
				//�Փ˓_�̋��������߂�
				Vector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (dist > distTmp)
				{
					//���̏Փ˓_�̂ق����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����
					hitPos = hitPosTmp;
					hitNormal = *(Vector3*)&rayResult.m_hitNormalLocal;
					dist = distTmp;
				}
			}
			return 0.0f;
		}
	};
	//�Փ˂������ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
	struct SweepResultWall : public btCollisionWorld::RayResultCallback
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
			//�n�ʂ̌X�΂�54�x�ȏ�Ȃ̂ŕǂƂ݂Ȃ��B
			if (angle >= Math::PI * 0.3f)
			{
				isHit = true;
				Vector3 hitPosTmp;
				hitPosTmp.Set(rayResult.m_hitNormalLocal);
				//��_�Ƃ̋����𒲂ׂ�B
				Vector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				vDist.y = 0.0f;
				float distTmp = vDist.Length();
				if (distTmp < dist)
				{
					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
					hitPos = hitPosTmp;
					dist = distTmp;
					hitNormal = hitNormalTmp;
				}
			}
			return 0.0f;
		}
	};

	Decale::Decale()
	{

	}

	Decale::~Decale()
	{

	}

	void Decale::Update()
	{
		//���s���e�s����쐬
		Matrix m_proj = Matrix::Identity;
		m_proj.MakeOrthoProjectionMatrix(10.0f, 10.0f, 0.0f, 10.0f);
		//���C���쐬
		btVector3 start, end;
		start.setZero();
		end.setZero();
		for (int i = 0; i < PosNum; i++)
		{
			//�n�_���Z�b�g
			start.setValue(m_StartPos[i].x, m_StartPos[i].y, m_StartPos[i].z);
			//�I�_�ƂȂ�ʒu���쐬
			Vector3 EndPos = Vector3::Zero;
			//�I�_�͎n�_�ƂȂ�ʒu�ɕ���*�����𑫂�������
			EndPos = m_StartPos[i];
			Vector3 Direction = Vector3::Zero;
			Direction = m_Direction[i];
			//�����𐳋K��
			Direction.Normalize();
			//���K�����������ɋ�����������
			Direction *= Distance;
			//�I�_�ɑ���
			EndPos += Direction;
			//�I�_���Z�b�g
			end.setValue(EndPos.x, EndPos.y, EndPos.z);

			//�Փˌ��o
			SweepResultWall callback;
			callback.startPos = m_StartPos[i];
			//�Փˌ��o
			g_engine->GetPhysicsWorld().RayTest(start, end, callback);

			if (callback.isHit)
			{
				btVector3 hitPosTmp = start + (end - start) * callback.m_closestHitFraction;
				//�����I�u�W�F�N�g�ƏՓ˂���
				Vector3 hitPos;
				hitPos.Set(hitPosTmp);
				//�J������ݒu���邽�߂ɏ����߂Â���
				hitPos -= Direction * 5.0f;
				//�J�����s�����邽�߂Ƀ^�[�Q�b�g�|�W�V�������쐬
				Vector3 targetPos = callback.hitPos;
				//�^�[�Q�b�g�͏�������
				targetPos += Direction * 5.0f;
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
				m_DecaleVP.push_back(m_VP);
			}
		}
	}
}