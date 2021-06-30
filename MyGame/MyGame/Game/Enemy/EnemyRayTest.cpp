#include "stdafx.h"
#include "EnemyRayTest.h"

//�Փ˂������ɌĂ΂��֐��I�u�W�F�N�g
struct SweepResult : public btCollisionWorld::RayResultCallback
{
	bool isHit = false;						//�Փ˃t���O�B
	btScalar ObjectNearDist = 10000.0;
	btScalar GhostDist = 10000.0;
	//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool /*normalInWorldSpace*/)
	{
		if (rayResult.m_collisionObject->getUserIndex() == enCollisionAttr_StaticObject)
		{
			//�X�^�e�B�b�N�I�u�W�F�N�g�ɂԂ������Ƃ�
			if (rayResult.m_hitFraction < ObjectNearDist)
			{
				ObjectNearDist = rayResult.m_hitFraction;
			}
			return 0.0f;
		}
		else if (rayResult.m_collisionObject->getUserIndex() == enCollisionAttr_Player)
		{
			//�v���C���[�ɂԂ������Ƃ�
			if (rayResult.m_hitFraction < GhostDist)
			{
				GhostDist = rayResult.m_hitFraction;
			}
			m_collisionObject = rayResult.m_collisionObject;
			//�Փ˓_�̖@��
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(rayResult.m_hitNormalLocal);

			isHit = true;

			if (rayResult.m_hitFraction < m_closestHitFraction)
			{
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
				m_closestHitFraction = rayResult.m_hitFraction;
			}

			return rayResult.m_hitFraction;
		}

		return rayResult.m_hitFraction;
	}
};

bool EnemyRayTest::Start()
{

	return true;
}

bool EnemyRayTest::IsHit(Vector3& pos, Vector3& dir)
{
	//���C���쐬
	btVector3 start, end;
	start.setZero();
	end.setZero();

	//�n�_���Z�b�g
	start.setValue(pos.x, pos.y, pos.z);
	//�I�_���v�Z
	Vector3 EndPos = Vector3::Zero;
	//�n�_����
	EndPos = pos;
	//���Ă�������ɋ������|�������̂����Z
	EndPos += dir * m_visualDist;
	end.setValue(EndPos.x, EndPos.y, EndPos.z);

	//�Փˌ��o
	SweepResult callback;
	g_engine->GetPhysicsWorld().RayTest(start, end, callback);
	//���C���S�[�X�g�I�u�W�F�N�g�Ƀq�b�g���Ă���Ƃ�
	if (callback.isHit)
	{
		//�I�u�W�F�N�g�̎�O�ɉ����Ȃ��Ƃ�
		if (callback.GhostDist < callback.ObjectNearDist)
		{
			//�q�b�g���Ă���̂�true��Ԃ�
			return true;
		}
	}

	//�q�b�g���Ă��Ȃ��̂�false��Ԃ�
	return false;
}