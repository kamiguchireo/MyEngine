#include "stdafx.h"
#include "CharacterController.h"

namespace Engine {
	namespace {
		//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
		struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;		//�Փ˃t���O
			Vector3 hitPos = Vector3(0.0f, -FLT_MAX, 0.0f);		//�Փ˓_
			Vector3 startPos = Vector3::Zero;		//���C�̎n�_
			Vector3 hitNormal = Vector3::Zero;		//�Փ˓_�̖@��
			btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂�������邽�߂̃����o
			float dist = FLT_MAX;		//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁B

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
			virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
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
	}

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
		//�������L�����R���ɂ���
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
		//�t�B�W�b�N�X���[���h�ɓo�^
		g_engine->GetPhysicsWorld() .AddRigidBody(m_rigidBody);
		m_isInited = true;
	}

	const Vector3& CharacterController::Execute(Vector3& moveSpeed, float deltaTime)
	{
		//����������Ă��Ȃ��L�����N�^�[�R���g���[���[���g��ꂽ�Ƃ�
		if (m_isInited == false)
		{
			//�������~
			std::abort();
		}

		if (moveSpeed.y > 0.0f)
		{
			//�W�����v���ɂ���
			m_isJump = true;
			m_isOnGround = false;
		}
		//���̈ړ���ƂȂ���W���v�Z����
		Vector3 nextPosition = m_position;
		//���x���炱�̃t���[���ł̈ړ��ʂ����߂�B
		//�I�C���[�ϕ�
		Vector3 addPos = moveSpeed;
		addPos.Scale(deltaTime);
		nextPosition.Add(addPos);
		Vector3 originalXZDir = addPos;
		originalXZDir.y = 0.0f;
		originalXZDir.Normalize();
		//XZ���ʂł̏Փˌ��o�ƏՓˉ������s��
		int loopCount = 0;
		while (true)
		{
			//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�
			Vector3 addPos;
			//���Z
			addPos.Subtract(nextPosition, m_position);
			Vector3 addPosXZ = addPos;
			addPosXZ.y = 0.0f;
			if (addPosXZ.Length() < FLT_EPSILON)
			{
				//XZ���ʂœ������Ȃ��̂Œ��ׂȂ��Ă悢
				//FLT_EPSILON�͂ƂĂ��������l�̂���
				break;
			}
			Vector3 posTmp = m_position;
			//�J�v�Z���R���C�_�[�̒��S���W + ����*0.1f�̍��W��posTmp�ɋ��߂�
			posTmp.y += m_height * 0.5f + m_radius + m_height * 0.1f;
			//���C���쐬
			btTransform start, end;
			//�n�_
			start.setIdentity();
			//�I�_
			end.setIdentity();
			//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2f�̍��W��posTmp�ɋ��߂�
			start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
			//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��
			end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

			SweepResultWall callback;
			callback.me = m_rigidBody.GetBody();
			callback.startPos = posTmp;
			//�Փˌ��o
			g_engine->GetPhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);

			//���������Ƃ�
			if (callback.isHit)
			{
				//��
				Vector3 vT0, vT1;
				//XZ���ʏ�ł̈ٓ���̍��W��vT0�ɁA��_�̍��W��vT1�ɐݒ肷��
				vT0.Set(nextPosition.x, 0.0f, nextPosition.z);
				vT1.Set(callback.hitPos.x, 0.0f, callback.hitPos.z);
				//�߂荞�݂��������Ă���ړ��x�N�g�������߂�
				Vector3 vMerikomi;
				vMerikomi.Subtract(vT0, vT1);
				//XZ���ʂł̏Փ˂����ǂ̖@�������߂�
				Vector3 hitNormalXZ = callback.hitNormal;
				hitNormalXZ.y = 0.0f;
				hitNormalXZ.Normalize();
				//�߂荞�݃x�N�g����ǂ̖@���Ɏˉe����
				float fT0 = hitNormalXZ.Dot(vMerikomi);
				//�����Ԃ��x�N�g�������߂�
				//�����Ԃ��x�N�g���͕ǂ̖@���Ɏˉe���ꂽ�߂荞�݃x�N�g�� + ���a
				Vector3 vOffset;
				vOffset = hitNormalXZ;
				vOffset.Scale(-fT0 + m_radius);
				nextPosition.Add(vOffset);
				Vector3 currentDir;
				currentDir.Subtract(nextPosition, m_position);
				currentDir.y = 0.0f;
				currentDir.Normalize();
				if (currentDir.Dot(originalXZDir) < 0.0f)
				{
					//�ړ��悪�t�����ɂȂ�����ړ����L�����Z��
					nextPosition.x = m_position.x;
					nextPosition.z = m_position.z;
					break;
				}
			}
			else
			{
				//�ǂ��ɂ�������Ȃ������Ƃ�
				break;
			}
			loopCount++;
			if (loopCount == 5)
			{
				break;
			}
		}
		//XZ�̈ړ��͊m��
		m_position.x = nextPosition.x;
		m_position.z = nextPosition.z;
		
		//�������𒲂ׂ�
		Vector3 AddPos;
		AddPos.Subtract(nextPosition, m_position);
		m_position = nextPosition;		//�ړ��̉��m��
		//���C���쐬
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S
		start.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
		//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������
		//�n�ʏ�ɂ��Ȃ����ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������
		//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�
		Vector3 endPos;
		endPos.Set(start.getOrigin());
		//�󒆂ɂ���Ƃ�
		if (m_isOnGround == false)
		{
			//�㏸��
			if (AddPos.y > 0.0f)
			{
				//�㏸���ł�XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŉ��𒲂ׂ�
				endPos.y -= AddPos.y * 0.01f;
			}
			else
			{
				//�������Ă���Ƃ�
				endPos.y += AddPos.y;
			}
		}
		else
		{
			//�n�ʏ�ɂ��Ȃ��ꍇ��1m��������
			endPos.y -= 1.0f;
		}
		end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
		SweepResultGround callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos.Set(start.getOrigin());
		//�Փˌ��o
		if (fabsf(endPos.y - callback.startPos.y) > FLT_EPSILON)
		{
			g_engine->GetPhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
			if (callback.isHit)
			{
				//��������
				moveSpeed.y = 0.0f;
				m_isJump = false;
				m_isOnGround = true;
				nextPosition.y = callback.hitPos.y;
			}
			else
			{
				//�n�ʏ�ɂ��Ȃ�
				m_isOnGround = false;
			}
		}
		//�ړ��m��
		m_position = nextPosition;
		btRigidBody* btBody = m_rigidBody.GetBody();
		//���̂𓮂���
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		//���̂̈ʒu���X�V
		trans.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
		return m_position;
	}

	//���S�������Ƃ�ʒm
	void CharacterController::RemoveRigidBody()
	{
		g_engine->GetPhysicsWorld().RemoveRigidBody(m_rigidBody);
	}
}
