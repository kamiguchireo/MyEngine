#include "stdafx.h"
#include "Animation.h"

namespace Engine
{
	void Animation::Init(Skeleton& skeleton,AnimationClip animClips[],int numAnimClip)
	{
		//�A�j���[�V�����N���b�v������̎�
		if (animClips == nullptr)
		{
			//�A�j���[�V�����N���b�v������ł�
			std::abort();
		}
		m_skeleton = &skeleton;

		//�A�j���[�V�����N���b�v�̐�������
		for (int i = 0; i < numAnimClip; i++)
		{
			m_animationClips.push_back(&animClips[i]);
		}

		//footStep�{�[���̔ԍ��𒲂ׂ�
		int footsteoBoneNo = -1;
		int numBone = m_skeleton->GetNumBones();
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			auto bone = m_skeleton->GetBone(boneNo);
			//footstep�Ŗ��O����
			if (wcscmp(bone->GetName(), L"footstep") == 0)
			{
				//footstep�{�[�����݂�����
				footsteoBoneNo = boneNo;
				break;
			}
		}

		for (auto& ctr : m_animationPlayController)
		{
			ctr.Init(m_skeleton, footsteoBoneNo);
		}
		Play(0);
		m_isInited = true;
	}

	//�A�j���[�V�����̍Đ�
	void Animation::PlayCommon(AnimationClip*nextClip,float interpolateTime)
	{
		if (nextClip->IsLoaded() == false)
		{
			//�A�j���[�V�����N���b�v�����[�h����Ă��܂���B
			std::abort();
		}
		//�ŏI�|�[�Y�ƂȂ�A�j���[�V�����N���b�v�̃C���f�b�N�X���擾
		int index = GetLastAnimationControllerIndex();
		//�A�j���[�V�����N���b�v��1�̎��⊮�����ɏI��
		if (m_animationPlayController[index].GetAnimClip() == nextClip)
		{
			return;
		}
		if (interpolateTime == 0.0f)
		{
			//�⊮�Ȃ�
			m_numAnimationPlayController = 1;
		}
		else 
		{
			//�⊮����
			m_numAnimationPlayController++;
		}
		index = GetLastAnimationControllerIndex();
		//�A�j���[�V�����N���b�v�̐؂�ւ�
		m_animationPlayController[index].ChangeAnimationClip(nextClip);
		m_animationPlayController[index].SetInterpolateTime(interpolateTime);
		m_interpolateTime = 0.0f;
		m_interpolateTimeEnd = interpolateTime;
	}

	//���[�J���|�[�Y�̍X�V
	void Animation::UpdateLocalPose(float deltaTime)
	{
		//�⊮���Ԃ�i�߂Ă���
		m_interpolateTime += deltaTime;
		if (m_interpolateTime >= 1.0f)
		{
			//�⊮����
			//���݂̍ŏI�A�j���[�V�����R���g���[���ւ̃C���f�b�N�X���J�n�C���f�b�N�X�ɂȂ�
			m_startAnimationPlayController = GetLastAnimationControllerIndex();
			m_numAnimationPlayController = 1;
			m_interpolateTime = 1.0f;
		}
		for (int i = 0; i < m_numAnimationPlayController - 1; i++)
		{
			int index = GetAnimationControllerIndecx(m_startAnimationPlayController, i);
			m_animationPlayController[index].Update(deltaTime/*, this*/);
		}
		//�Ō�̃|�[�Y�����i�߂�
		int lastIndex = GetLastAnimationControllerIndex();
		m_animationPlayController[lastIndex].Update(deltaTime/*, this*/);

	}

	Vector3 Animation::UpdateGlobalPose()
	{
		//�O���[�o���|�[�Y�v�Z�p�̃��������m��
		int numBone = m_skeleton->GetNumBones();
		Quaternion* qGlobalPose = (Quaternion*)_malloca(sizeof(Quaternion) * numBone);
		Vector3* vGlobalPose = (Vector3*)_malloca(sizeof(Vector3) * numBone);
		Vector3* vGlobalScale = (Vector3*)_malloca(sizeof(Vector3) * numBone);
		for (int i = 0; i < numBone; i++)
		{
			//NULL�`�F�b�N
			if (qGlobalPose)
			{
				qGlobalPose[i] = Quaternion::Identity;
			}
			//NULL�`�F�b�N
			if (vGlobalPose)
			{
				vGlobalPose[i] = Vector3::Zero;
			}
			//NULL�`�F�b�N
			if (vGlobalScale)
			{
				vGlobalScale[i] = Vector3::One;
			}
		}
		//�O���[�o���|�[�Y���v�Z
		int startIndex = m_startAnimationPlayController;
		//�A�j���[�V�����Đ��R���g���[���[�̐�����
		for (int i = 0; i < m_numAnimationPlayController; i++)
		{
			int index = GetAnimationControllerIndecx(startIndex, i);
			float interpolateRate = m_animationPlayController[index].GetInterpolateRate();
			const auto& localBoneMatrix = m_animationPlayController[index].GetBoneLocalMatrix();
			for (int boneNo = 0; boneNo < numBone; boneNo++)
			{
				//���s�ړ��̕⊮
				Matrix m = localBoneMatrix[boneNo];
				//NULL�`�F�b�N
				if (vGlobalPose)
				{
					vGlobalPose[boneNo].Lerp(interpolateRate, vGlobalPose[boneNo], *(Vector3*)m.m[3]);
				}
				//���s�ړ��������폜
				m.m[3][0] = 0.0f;
				m.m[3][1] = 0.0f;
				m.m[3][2] = 0.0f;

				//�g�听���̕⊮
				Vector3 vBoneScale;
				vBoneScale.x = (*(Vector3*)m.m[0]).Length();
				vBoneScale.y = (*(Vector3*)m.m[1]).Length();
				vBoneScale.z = (*(Vector3*)m.m[2]).Length();

				//NULL�`�F�b�N
				if (vGlobalScale)
				{
					vGlobalScale[boneNo].Lerp(interpolateRate, vGlobalScale[boneNo], vBoneScale);
				}
				//�g�听��������
				m.m[0][0] /= vBoneScale.x;
				m.m[0][1] /= vBoneScale.x;
				m.m[0][2] /= vBoneScale.x;

				m.m[1][0] /= vBoneScale.y;
				m.m[1][1] /= vBoneScale.y;
				m.m[1][2] /= vBoneScale.y;

				m.m[2][0] /= vBoneScale.z;
				m.m[2][1] /= vBoneScale.z;
				m.m[2][2] /= vBoneScale.z;

				//��]�̕⊮
				Quaternion qBone = Quaternion::Identity;
				qBone.SetRotation(m);
				//NULL�`�F�b�N
				if (qGlobalPose)
				{
					qGlobalPose[boneNo].Slerp(interpolateRate, qGlobalPose[boneNo], qBone);
				}

			}
		}
		//�O���[�o���|�[�Y���X�P���g���ɔ��f������
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			//�g��s����쐬
			Matrix scaleMatrix;
			//NULL�`�F�b�N
			if (vGlobalScale)
			{
				scaleMatrix.MakeScaling(vGlobalScale[boneNo]);
			}
			//��]�s����쐬
			Matrix rotMatrix;
			//NULL�`�F�b�N
			if (qGlobalPose)
			{
				rotMatrix.MakeRotationFromQuaternion(qGlobalPose[boneNo]);
			}
			//���s�ړ��s����쐬
			Matrix transMat;
			//NULL�`�F�b�N
			if (vGlobalPose)
			{
				transMat.MakeTranslation(vGlobalPose[boneNo]);
			}
			//�S�����������āA�{�[���s����쐬
			Matrix boneMatrix;
			boneMatrix = scaleMatrix * rotMatrix;
			boneMatrix = boneMatrix * transMat;

			m_skeleton->SetBoneLocalMatrix(
				boneNo,
				boneMatrix
			);

			m_skeleton->GetBone(boneNo)->CalcWorldTRS(vGlobalPose[boneNo], qGlobalPose[boneNo], vGlobalScale[boneNo]);
			
		}
		//�ŏI�A�j���[�V�����ȊO�͕⊮�������Ă����珜������
		int numAnimationPlayController = m_numAnimationPlayController;
		for (int i = 1; i < m_numAnimationPlayController; i++)
		{
			int index = GetAnimationControllerIndecx(startIndex, i);
			if (m_animationPlayController[index].GetInterpolateRate() > 0.99999f)
			{
				//�⊮���I����Ă���̂ŃA�j���[�V�����̊J�n�ʒu��O�ɂ���
				m_startAnimationPlayController = index;
				numAnimationPlayController = m_numAnimationPlayController - i;
			}
		}
		m_numAnimationPlayController = numAnimationPlayController;
		int lastAnimClip = GetLastAnimationControllerIndex();
		auto m_footstepDeltaValue = m_animationPlayController[lastAnimClip].GetFootStepDeltaValueOnUpdate();
		//footstep�̈ړ��ʂ̕⊮
		//m_footstepDeltaValue.Lerp(interpolateRate, m_footstepDeltaValue, deltaValueFootStep);

		return m_footstepDeltaValue;
	}

	Vector3 Animation::Update(float deltaTime)
	{
		if (m_numAnimationPlayController == 0)
		{
			//�A�j���[�V�����v���C�R���g���[���̐����s���ł�
			std::abort();
		}
		//���[�J���|�[�Y�̍X�V
		UpdateLocalPose(deltaTime);

		//�O���[�o���|�[�Y���v�Z
		return UpdateGlobalPose();
	}
}