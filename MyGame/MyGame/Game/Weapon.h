#pragma once
#include "SourceFile/sound/SoundSource.h"
class SoundSource;
class Weapon:public IGameObject
{
	//�Փ˂������ɌĂ΂��֐��I�u�W�F�N�g
	struct SweepResult : public btCollisionWorld::RayResultCallback
	{
		void SetFireCharacter(int i)
		{
			FireCharacter = i;
		}
		int FireCharacter = enCollisionAttr_Num;
		bool isHit = false;						//�Փ˃t���O�B
		//Vector3 hitPos = Vector3::Zero;		//�Փ˓_�B
		//Vector3 startPos = Vector3::Zero;		//���C�̎n�_�B
		btScalar ObjectNearDist = 10000.0;
		btScalar GhostDist = 10000.0;
		//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool /*normalInWorldSpace*/)
		{
			int UserIndex = rayResult.m_collisionObject->getUserIndex();

			if (UserIndex == FireCharacter)
			{
				return 0.0f;
			}
			//�S�[�X�g�I�u�W�F�N�g�ƃL�����R���ȊO�ɏՓ˂����Ƃ�
			if (UserIndex == enCollisionAttr_StaticObject)
			{
				if (rayResult.m_hitFraction < ObjectNearDist)
				{
					ObjectNearDist = rayResult.m_hitFraction;
				}
				return 0.0f;
			}
			if (rayResult.m_collisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT)
			{
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
			}
			return rayResult.m_hitFraction;
		}
	};
public:
	Weapon(){}
	~Weapon();
	void OnDestroy();
	bool Start();
	void Update();

	//������
	//sk		�X�P���g��
	//IsDither		�f�B�U�����O��K�����邩�ǂ����̃t���O
	void Init(Skeleton* sk,bool IsDither = false);

	//�ˌ�
	//�߂�l�͎ˌ��ł������ǂ���
	bool shooting();

	//�ˌ�����߂����̏���
	void Release()
	{
		m_IsFirstShoot = true;
	}
	bool IsAvailable()
	{
		if (m_Magazine > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void SetRay(const Vector3& startpos,const Vector3& dir)
	{
		m_RayStartPos = startpos;
		m_RayDirection = dir;
	}

	void StopFireSound(int i)
	{
		m_FireSound[i]->Stop();
	}

	void SetCharacter(int i)
	{
		Character = i;
	}
private:
	//�f�J�[����ǉ�
	//start		�n�_
	//end		�I�_
	void AddDecale(const btVector3& start, const btVector3& end);

private:
	Skeleton* m_skeleton = nullptr;		//�X�P���g��
	Vector3 m_weaponPos = Vector3::Zero;		//����̃|�W�V����
	Quaternion m_weaponRot = Quaternion::Identity;		//����̉�]
	Matrix m_weaponMat = Matrix::Identity;		//����̍s��
	prefab::ModelRender* m_Model = nullptr;		//���f��
	int LeftHandBoneNo = -1;		//����p�̃{�[���ԍ�
	const float m_range = 10000.0f;		//�˒�
	const int rate = 10;
	float time = 0.0f;
	Vector3 m_RayStartPos = Vector3::Zero;
	Vector3 m_RayDirection = Vector3::Zero;
	SoundSource* m_FireSound[FireSoundNum_Rifle] = { nullptr };
	SoundSource* m_OutOfAmmoSound = nullptr;
	int Character = enCollisionAttr_Num;
	const float m_FireCurveDistance = 3000.0f;
	const float m_OutOfAmmoCurveDistance = 500.0f;
	int m_Magazine = 30;
	bool m_IsFirstShoot = true;
};

