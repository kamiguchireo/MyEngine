#include "stdafx.h"
#include "Weapon.h"

//�Փ˂������ɌĂ΂��֐��I�u�W�F�N�g
struct SweepResult : public btCollisionWorld::RayResultCallback
{
	bool isHit = false;						//�Փ˃t���O�B
	Vector3 hitPos = Vector3::Zero;		//�Փ˓_�B
	Vector3 startPos = Vector3::Zero;		//���C�̎n�_�B

	//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool /*normalInWorldSpace*/)
	{
		//�S�[�X�g�I�u�W�F�N�g�ȊO�ɏՓ˂����Ƃ�
		if (rayResult.m_collisionObject->getInternalType() != btCollisionObject::CO_GHOST_OBJECT)
		{
			return 0.0f;
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

Weapon::~Weapon()
{
	//�������
	if (m_Model != nullptr)
	{
		DeleteGO(m_Model);
		m_Model = nullptr;
	}

}

void Weapon::Init(Skeleton* sk,bool IsDither)
{
	m_skeleton = sk;
	//���f����New
	m_Model = NewGO<prefab::ModelRender>(3);
	//�t�@�C���p�X���Z�b�g
	m_Model->SetTkmFilePath("Assets/modelData/AK_74M.tkm");
	//�f�B�U�����O��K�����邩�ǂ����̃t���O
	m_Model->SetDitherFlag(IsDither);
}
bool Weapon::Start()
{
	LeftHandBoneNo = m_skeleton->FindBoneID(L"mixamorig:LeftHand");

	return true;
}

void Weapon::AddDecale(const btVector3& start,const btVector3& end)
{
	g_graphicsEngine->GetDecale()->AddStartPos(start , end);
}

void Weapon::Update()
{
	//����p�̍s����{�[������擾
	m_weaponMat = m_skeleton->GetWeaponMatrix();
	//����Ƀ��[���h�s����Z�b�g
	m_Model->SetWorldMatrix(m_weaponMat);
	//���ڍs����Z�b�g���Ă���̂ōs��̌v�Z�͂��Ȃ�
	m_Model->SetUpdateFlag(false);
}

void Weapon::shooting()
{
	//���C���쐬
	btVector3 start, end;
	start.setZero();
	end.setZero();

	//�J�����̈ʒu
	Vector3 cameraPos = g_camera3D->GetPosition();
	//�J�����̌���
	Vector3 Direction = g_camera3D->GetTarget() - g_camera3D->GetPosition();
	//�����𐳋K��
	Direction.Normalize();

	//�n�_���Z�b�g
	start.setValue(cameraPos.x, cameraPos.y, cameraPos.z);

	//�I�_�ƂȂ�ʒu���쐬
	Vector3 EndPos = Vector3::Zero;
	//�I�_�͎n�_�ƂȂ�ʒu�ɕ���*�����𑫂�������
	EndPos = cameraPos;
	//�I�_�ɕ����ɋ������|�������̑���
	EndPos += Direction * m_range;
	//�I�_���Z�b�g
	end.setValue(EndPos.x, EndPos.y, EndPos.z);



	//�Փˌ��o
	SweepResult callback;
	//�Փˌ��o
	g_engine->GetPhysicsWorld().RayTest(start, end, callback);

	//���C���S�[�X�g�I�u�W�F�N�g�ɏՓ˂��Ă���Ƃ�
	if (callback.isHit)
	{
		callback.m_collisionObject->setActivationState(CollisionActivationState::Hit);
		int i = callback.m_collisionObject->getActivationState();
		return;
	}

	//�Փ˂��Ă��Ȃ���΃f�J�[����ǉ�
	AddDecale(start, end);
}