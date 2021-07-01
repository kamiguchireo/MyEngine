#pragma once

class Weapon:public IGameObject
{
	//�Փ˂������ɌĂ΂��֐��I�u�W�F�N�g
	struct SweepResult : public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;						//�Փ˃t���O�B
		//Vector3 hitPos = Vector3::Zero;		//�Փ˓_�B
		//Vector3 startPos = Vector3::Zero;		//���C�̎n�_�B
		btScalar ObjectNearDist = 10000.0;
		btScalar GhostDist = 10000.0;
		//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool /*normalInWorldSpace*/)
		{
			//�S�[�X�g�I�u�W�F�N�g�ƃL�����R���ȊO�ɏՓ˂����Ƃ�
			if (rayResult.m_collisionObject->getInternalType() != btCollisionObject::CO_GHOST_OBJECT
				&& rayResult.m_collisionObject->getUserIndex() != enCollisionAttr_Character)
			{
				if (rayResult.m_hitFraction < ObjectNearDist)
				{
					ObjectNearDist = rayResult.m_hitFraction;
				}
				return 0.0f;
			}
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
	};
public:
	Weapon() {}
	~Weapon();
	bool Start();
	void Update();

	//������
	//sk		�X�P���g��
	//IsDither		�f�B�U�����O��K�����邩�ǂ����̃t���O
	void Init(Skeleton* sk,bool IsDither = false);

	//�ˌ�
	void shooting();

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
};

