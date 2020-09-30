#include "stdafx.h"
#include "Animation.h"

namespace Engine
{
	void Animation::Init(Skeleton& skeleton, const std::vector<std::unique_ptr<AnimationClip>>&animClips)
	{
		//�A�j���[�V�����N���b�v������̎�
		if (animClips.empty() == true)
		{
			//�A�j���[�V�����N���b�v������ł�
			std::abort();
		}
		m_skeleton = &skeleton;

		//�A�j���[�V�����N���b�v�̐�������
		for (auto& animClip : animClips)
		{
			m_animationClips.push_back(animClip.get());
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
			m_animationPlayController[index].Update(deltaTime, this);
		}
		//�Ō�̃|�[�Y�����i�߂�
		int lastIndex = GetLastAnimationControllerIndex();
		m_animationPlayController[lastIndex].Update(deltaTime, this);

	}

	void Animation::UpdateGlobalPose()
	{
		//�O���[�o���|�[�Y�v�Z�p�̃��������m��
		int numBone = m_skeleton->GetNumBones();
		Quaternion* qGlobalPose = (Quaternion*)alloca(sizeof(Quaternion) * numBone);
		Vector3* vGlobalPose = (Vector3*)alloca(sizeof(Vector3) * numBone);
		Vector3* vGlobalScale = (Vector3*)alloca(sizeof(Vector3) * numBone);
		//footstep�̈ړ��ʂ�������
		m_footstepDeltaValue = g_vec3Zero;
		for (int i = 0; i < numBone; i++)
		{
			qGlobalPose[i] = Quaternion::Identity;
			vGlobalPose[i] = Vector3::Zero;
			vGlobalScale[i] = Vector3::One;
		}
		//�O���[�o���|�[�Y���v�Z
		int startIndex = m_startAnimationPlayController;
		for (int i = 0; i < m_numAnimationPlayController; i++)
		{
			int index = GetAnimationControllerIndecx(startIndex, i);
			float interpolateRate = m_animationPlayController[index].GetInterpolateRate();
			const auto& localBoneMatrix = m_animationPlayController[index].GetBoneLocalMatrix();
			auto deltaValueFootStep = m_animationPlayController[index].GetFootStepDeltaValueOnUpdate();
			//footstep�̈ړ��ʂ̕⊮
			m_footstepDeltaValue.Lerp(interpolateRate, m_footstepDeltaValue, deltaValueFootStep);
			for (int boneNo = 0; boneNo < numBone; boneNo++)
			{
				//���s�ړ��̕⊮
				Matrix m = localBoneMatrix[boneNo];
				vGlobalPose[boneNo].Lerp(interpolateRate, vGlobalPose[boneNo], *(Vector3*)m.m[3]);
				//���s�ړ��������폜
				m.m[3][0] = 0.0f;
				m.m[3][1] = 0.0f;
				m.m[3][2] = 0.0f;

				//�g�听���̕⊮
				Vector3 vBoneScale;
				vBoneScale.x = (*(Vector3*)m.m[0]).Length();
				vBoneScale.x = (*(Vector3*)m.m[1]).Length();
				vBoneScale.x = (*(Vector3*)m.m[2]).Length();

				vGlobalScale[boneNo].Lerp(interpolateRate, vGlobalScale[boneNo], vBoneScale);
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
				Quaternion qBone;
				qBone.SetRotation(m);
				qGlobalPose[boneNo].Slerp(interpolateRate, qGlobalPose[boneNo], qBone);
			}
		}
		//�O���[�o���|�[�Y���X�P���g���ɔ��f������
		for (int boneNo = 0; boneNo < numBone; boneNo++)
		{
			//�g��s����쐬
			Matrix scaleMatrix;
			scaleMatrix.MakeScaling(vGlobalScale[boneNo]);
			//��]�s����쐬
			Matrix rotMatrix;
			rotMatrix.MakeRotationFromQuaternion(qGlobalPose[boneNo]);
			//���s�ړ��s����쐬
			Matrix transMat;
			transMat.MakeTranslation(vGlobalPose[boneNo]);

			//�S�����������āA�{�[���s����쐬
			Matrix boneMatrix;
			boneMatrix = scaleMatrix * rotMatrix;
			boneMatrix = boneMatrix * transMat;

			m_skeleton->SetBoneLocalMatrix(
				boneNo,
				boneMatrix
			);
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
	}

	void Animation::Progress(float deltaTime)
	{
		if (m_numAnimationPlayController == 0)
		{
			//�A�j���[�V�����v���C�R���g���[���̐����s���ł�
			std::abort();
		}
		m_deltaTimeOnUpdate = deltaTime;
		//���[�J���|�[�Y�̍X�V
		UpdateLocalPose(deltaTime);

		//�O���[�o���|�[�Y���v�Z
		UpdateGlobalPose();
	}
}