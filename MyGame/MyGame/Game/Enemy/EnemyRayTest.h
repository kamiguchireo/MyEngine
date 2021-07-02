#pragma once

class Enemy;
class EnemyRayTest
{
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

public:
	EnemyRayTest(Enemy* en) :m_enemy(en) {}
	~EnemyRayTest() {}

	bool Start();

	//pos		���C�̎n�_
	//dir		���C�̕���
	bool IsHit(Vector3& pos, Vector3& dir);

	void Update(Vector3 pl_pos);

private:	
	Enemy* m_enemy = nullptr;
	const float m_visualDist = 1000.0f;		//���C�͈̔�
	const float m_RayWaitTime = 0.5f;		//���C�`�F�b�N����p�x
	float m_NowWaitTime = 0.0f;
	SweepResult callback;		//�Փˌ��o
};