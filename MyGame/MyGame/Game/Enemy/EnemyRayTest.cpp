#include "stdafx.h"
#include "EnemyRayTest.h"
#include "Enemy.h"

bool EnemyRayTest::Start()
{
	return true;
}

bool EnemyRayTest::IsHit(Vector3& pos, Vector3& dir,float dist)
{
	callback.Reset();
	//���C���쐬
	btVector3 start, end;
	start.setZero();
	end.setZero();

	//�n�_���Z�b�g
	start.setValue(pos.x, pos.y+50.0f, pos.z);
	//�I�_���v�Z
	Vector3 EndPos = Vector3::Zero;
	//�n�_����
	EndPos = pos;
	EndPos.y += 50.0f;
	//���Ă�������ɋ������|�������̂����Z
	EndPos += dir * (dist + 100);

	end.setValue(EndPos.x, EndPos.y, EndPos.z);

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

void EnemyRayTest::Update(Vector3 pl_pos)
{		
	//���݂̎��Ԃ����Z
	m_NowWaitTime += g_gameTime.GetFrameDeltaTime();
	//��莞�Ԃ��ƂɃ��C�e�X�g
	if (m_NowWaitTime >= m_RayWaitTime)
	{

		if (m_enemy->CanSeePlayer())
		{
			Vector3 enemyPos = m_enemy->GetPosition();
			//���C�̎n�_
			Vector3 RayStart = enemyPos;

			//���C�̕���
			Vector3 RayDir = pl_pos - enemyPos;

			float ToPlayerDist = RayDir.Length();

			RayDir.Normalize();
			//�v���C���[�Ɍ����ă��C���΂��ĊԂɉ����Ȃ��Ƃ�
			if (IsHit(RayStart, RayDir, ToPlayerDist))
			{
				//�v���C���[�𔭌�������Ԃɂ���
				m_enemy->ChangeActState(EnemyActState::enState_Discover);
				callback.m_collisionObject->setActivationState(CollisionActivationState::Hit);
			}
			else
			{
				m_enemy->ChangeActState(EnemyActState::enState_Normal);
			}
			//�J�E���g��0�ɂ���
			m_NowWaitTime = 0.0f;
		}
	}
}