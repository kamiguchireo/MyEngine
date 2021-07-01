#include "stdafx.h"
#include "EnemyRayTest.h"


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