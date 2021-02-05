#include "stdafx.h"
#include "CharacterController.h"

namespace Engine {
	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
	struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;		//�Փ˃t���O
		Vector3 hitPos = Vector3(0.0f, -FLT_MAX, 0.0f);		//�Փ˓_
		Vector3 startPos = Vector3::Zero;		//���C�̎n�_
		Vector3 hitNormal = Vector3::Zero;		//�Փ˓_�̖@��
		btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂�������邽�߂̃����o
		float dist = FLT_MAX;		//�Փ˓X�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁B
																		
		//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐�
		virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			//�����ɏՓ˂����Ƃ�
			if (convexResult.m_hitCollisionObject == me
				|| convexResult.m_hitCollisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT
				)
				{
				return 0.0f;
			}

			//�Փ˓_�̖@��
			Vector3 hitNormalTmp = *(Vector3*)&convexResult.m_hitNormalLocal;
			//������Ɩ@���̂Ȃ��p�����߂�
			float angle = hitNormalTmp.Dot(Vector3::Up);
			angle = fabsf(acosf(angle));
			//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ�
			if (angle < Math::PI * 0.3f)
			{
				//�Փ˂��Ă���
				isHit = true;
				Vector3 hitPosTmp = *(Vector3*)&convexResult.m_hitPointLocal;
				//�Փ˓_�̋��������߂�
				Vector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (dist > distTmp)
				{
					//���̏Փ˓_�̂ق����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����
					hitPos = hitPosTmp;
					hitNormal = *(Vector3*)&convexResult.m_hitNormalLocal;
					dist = distTmp;
				}
			}
			return 0.0f;
		}
	};
	//�Փ˂������ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
	struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;						//�Փ˃t���O�B
		Vector3 hitPos = Vector3::Zero;		//�Փ˓_�B
		Vector3 startPos = Vector3::Zero;		//���C�̎n�_�B
		float dist = FLT_MAX;					//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
		Vector3 hitNormal = Vector3::Zero;	//�Փ˓_�̖@���B
		btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B

		//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual btScalar addSignalResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			//�������n�ʂɏՓ˂����Ƃ�
			if (convexResult.m_hitCollisionObject == me
				|| convexResult.m_hitCollisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT
				)
			{
				return 0.0f;
			}
			//�Փ˓_�̖@��
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(convexResult.m_hitNormalLocal);
			//������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�B
			float angle = fabsf(acosf(hitNormalTmp.Dot(Vector3::Up)));
			//�n�ʂ̌X�΂�54�x�ȏ�Ȃ̂ŕǂƂ݂Ȃ��B
			if (angle >= Math::PI * 0.3f)
			{
				isHit = true;
				Vector3 hitPosTmp;
				hitPosTmp.Set(convexResult.m_hitPointLocal);
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

	void CharacterController::Init(float radius, float height, const Vector3& position)
	{
		//�ʒu����
		m_position = position;
		//���a����
		m_radius = radius;
		//��������
		m_height = height;
		//�R���W�����쐬
		m_collider.Create(radius, height);

		//���̂�������
		RigidBodyInfo rbInfo;
		//�R���C�_�[����
		rbInfo.collider = &m_collider;
		//���ʂ���
		rbInfo.mass = 0.0f;
		//���̂��쐬
		m_rigidBody.Create(rbInfo);
		btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
		//���̂̈ʒu���X�V
		trans.setOrigin(btVector3(position.x, position.y + m_height * 0.5f + m_radius, position.z));
		m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		//g_graphicsEngine->GetPhysicsWorld() .AddRigidBody(m_rigidBody);
		m_isInited = true;
	}
}
