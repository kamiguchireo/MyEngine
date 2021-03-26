#include "stdafx.h"
#include "Decale.h"

namespace Engine {
	
	//�Փ˂������ɌĂ΂��֐��I�u�W�F�N�g
	struct SweepResult : public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;						//�Փ˃t���O�B
		Vector3 hitPos = Vector3::Zero;		//�Փ˓_�B
		Vector3 startPos = Vector3::Zero;		//���C�̎n�_�B
		float dist = FLT_MAX;					//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
		Vector3 hitNormal = Vector3::Zero;	//�Փ˓_�̖@���B

		//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
		{
			//�������n�ʂɏՓ˂����Ƃ�
			if (rayResult.m_collisionObject->getUserIndex() == enCollisionAttr_Character
				||rayResult.m_collisionObject->getInternalType() == btCollisionObject::CO_GHOST_OBJECT)
			{
				return 0.0f;
			}
			//�Փ˓_�̖@��
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(rayResult.m_hitNormalLocal);
			//������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�B
			float angle = fabsf(acosf(hitNormalTmp.Dot(Vector3::Up)));
		
			isHit = true;
				
			if (rayResult.m_hitFraction < m_closestHitFraction)
			{
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
				hitNormal = hitNormalTmp;
				m_closestHitFraction = rayResult.m_hitFraction;
			}
			
			return rayResult.m_hitFraction;
		}
	};

	Decale::Decale()
	{

	}

	Decale::~Decale()
	{

	}

	void Decale::Init()
	{
		//���j�[�N�|�C���^���쐬
		m_DecaleVP.reset(new Matrix[m_maxNum]);
		//�X�g���N�`���[�o�b�t�@��������
		m_STB.Init(
			sizeof(Matrix),
			m_maxNum,
			m_DecaleVP.get()
		);
		m_DecaleTex.InitFromDDSFile(L"Assets/Image/Bullet_hole.dds");
		for (int i = 0; i < m_maxNum; i++)
		{
			m_DecaleVP[i] =
			{
			0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f
			};
		}
	}
	void Decale::Update()
	{
		//Vector3 v[8] = {Vector3::Zero };

		//for (int i = 0; i < PosNum; i++)
		//{
		//	Vector3 toNear, toFar = { Vector3::Zero };
		//	//AABB��O�̍��W
		//	toNear = m_StartPos[i];
		//	//AABB���̍��W
		//	toFar = m_StartPos[i] + m_Direction[i] * Distance;
		//	//�����
		//	Vector3 toUp = Vector3::Zero;
		//	toUp = Cross(m_Direction[i], m_Right[i]);
		//	//���Z����E����
		//	Vector3 AddRightPos = m_Right[i] * m_SideLength;
		//	//���Z��������
		//	Vector3 AddUpPos = toUp * m_SideLength;

		//	//AABB���쐬����
		//	//��O�E��̍��W
		//	v[0] = toNear + AddRightPos + AddUpPos;
		//	//��O�E���̍��W
		//	v[1] = v[0] - (AddUpPos * 2.0f);
		//	//��O����̍��W
		//	v[2] = toNear - AddRightPos + AddUpPos;
		//	//��O�����̍��W
		//	v[3] = v[2] - (AddUpPos * 2.0f);

		//	//���E��̍��W
		//	v[4] = toFar + AddRightPos + AddUpPos;
		//	//���E���̍��W
		//	v[5] = v[4] - (AddUpPos * 2.0f);
		//	//������̍��W
		//	v[6] = toFar - AddRightPos + AddUpPos;
		//	//�������̍��W
		//	v[7] = v[6] - (AddUpPos * 2.0f);

		//	//�J�����s����쐬
		//	Matrix DecaleView = Matrix::Identity;
		//	//�J�����̉����Z�b�g
		//	DecaleView.m[0][0] = m_Right[i].x;
		//	DecaleView.m[0][1] = m_Right[i].y;
		//	DecaleView.m[0][2] = m_Right[i].z;
		//	DecaleView.m[0][3] = 0.0f;
		//	//�J�����̏���Z�b�g
		//	DecaleView.m[1][0] = toUp.x;
		//	DecaleView.m[1][1] = toUp.y;
		//	DecaleView.m[1][2] = toUp.z;
		//	DecaleView.m[1][3] = 0.0f;
		//	//�J�����̑O���Z�b�g
		//	DecaleView.m[2][0] = m_Direction[i].x;
		//	DecaleView.m[2][1] = m_Direction[i].y;
		//	DecaleView.m[2][2] = m_Direction[i].z;
		//	DecaleView.m[2][3] = 0.0f;
		//	//�J�����̃|�W�V�������Z�b�g
		//	DecaleView.m[3][0] = m_StartPos[i].x;
		//	DecaleView.m[3][1] = m_StartPos[i].y;
		//	DecaleView.m[3][2] = m_StartPos[i].z;
		//	DecaleView.m[3][3] = 1.0f;
		//	//�J�����r���[����
		//	DecaleView.Inverse(DecaleView);

		//	//��������\������8���_���v�Z�ł����̂ŁA���C�g��Ԃɍ��W��ϊ����āAAABB�����߂�
		//	Vector3 vMax = { -FLT_MAX,-FLT_MAX,-FLT_MAX };
		//	Vector3 vMin = { FLT_MAX, FLT_MAX, FLT_MAX };
		//	for (auto& vInLight : v)
		//	{
		//		//�x�N�g���ƍs��̏�Z
		//		DecaleView.Apply(vInLight);
		//		//�ő�l��ݒ�
		//		vMax.Max(vInLight);
		//		//�ŏ��l��ݒ�
		//		vMin.Min(vInLight);
		//	}
		//	//���ƍ���
		//	float w = vMax.x - vMin.x;
		//	float h = vMax.y - vMin.y;
		//	float far_z = -1.0f;
		//	far_z = vMax.z;

		//	Matrix m_proj = Matrix::Identity;
		//	m_proj.MakeOrthoProjectionMatrix(
		//		w,
		//		h,
		//		far_z / Distance,
		//		far_z
		//	);
		//	Matrix m_VP = Matrix::Identity;
		//	m_proj.Multiply(DecaleView, m_proj);
		//	m_VP = m_proj;

		//	m_DecaleVP[num] = m_VP;
		//	if (num == m_maxNum)
		//	{
		//		num = 0;
		//	}
		//	else
		//	{
		//		num++;
		//	}

		//}

		//���s���e�s����쐬
		Matrix m_proj = Matrix::Identity;

		m_proj.MakeOrthoProjectionMatrix(m_SideLength, m_SideLength, 0.0f, 10.0f);
		//���C���쐬
		btVector3 start, end;
		start.setZero();
		end.setZero();
		for (int i = 0; i < PosNum; i++)
		{
			//�n�_���Z�b�g
			start.setValue(m_StartPos[i].x, m_StartPos[i].y, m_StartPos[i].z);
			//�I�_�ƂȂ�ʒu���쐬
			Vector3 EndPos = Vector3::Zero;
			//�I�_�͎n�_�ƂȂ�ʒu�ɕ���*�����𑫂�������
			EndPos = m_StartPos[i];
			Vector3 Direction = Vector3::Zero;
			Direction = m_Direction[i];
			//�����𐳋K��
			Direction.Normalize();
			//�I�_�ɕ����ɋ������|�������̑���
			EndPos += Direction * Distance;
			//�I�_���Z�b�g
			end.setValue(EndPos.x, EndPos.y, EndPos.z);

			//�Փˌ��o
			SweepResult callback;
			callback.startPos = m_StartPos[i];
			//�Փˌ��o
			g_engine->GetPhysicsWorld().RayTest(start, end, callback);
			callback.hasHit();
			if (callback.isHit)
			{
				btVector3 hitPosTmp = start + (end - start) * callback.m_closestHitFraction;
				//�����I�u�W�F�N�g�ƏՓ˂���
				Vector3 hitPos;
				hitPos.Set(hitPosTmp);
				//�J������ݒu���邽�߂ɏ����߂Â���
				hitPos -= Direction * 1.0f;
				//�J�����s�����邽�߂Ƀ^�[�Q�b�g�|�W�V�������쐬
				Vector3 targetPos = hitPos;
				//�^�[�Q�b�g�͏�������
				targetPos += Direction * 1.0f;
				//�J�����s����쐬
				Matrix m_view = Matrix::Identity;
				//�J�����̑O����
				Vector3 cameraForward = Vector3::Front;
				cameraForward = g_camera3D->GetForward();
				//�J�����̉E����
				Vector3 ViewRight = Vector3::Right;
				ViewRight.Cross(Direction, cameraForward);
				//���K��
				ViewRight.Normalize();
				//�J�����̏����
				Vector3 CameraUpAxis = Vector3::Up;
				CameraUpAxis.Cross(ViewRight, Direction);
				//���K��
				CameraUpAxis.Normalize();

				//�J�����s����쐬
				m_view.MakeLookAt(hitPos, targetPos, CameraUpAxis);

				Matrix m_VP = Matrix::Identity;
				m_proj.Multiply(m_view, m_proj);
				m_VP = m_proj;
				m_DecaleVP[num] = m_VP;
				if (num == m_maxNum)
				{
					num = 0;
				}
				else
				{
					num++;
				}
			}
		}

		m_STB.Update(m_DecaleVP.get());
	}
}