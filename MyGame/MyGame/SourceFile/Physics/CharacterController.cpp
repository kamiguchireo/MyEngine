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

	};
}
