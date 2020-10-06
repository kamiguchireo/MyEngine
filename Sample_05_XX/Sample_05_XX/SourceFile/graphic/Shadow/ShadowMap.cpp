#include "stdafx.h"
#include "ShadowMap.h"

namespace Engine
{
	ShadowMap::ShadowMap()
	{

	}

	ShadowMap::~ShadowMap()
	{

	}

	Vector3 ShadowMap::CalcLightPosition(float lightHeight, Vector3 viewFrustomCenterPosition)
	{
		auto alpha = (lightHeight - viewFrustomCenterPosition.y) / lightDir.y;
		auto lightPos = viewFrustomCenterPosition + lightDir * alpha;
		return lightPos;
	}


	void ShadowMap::ShadowMapRTCreate()
	{
		int wh[][2] = {
			{TexResolution,TexResolution},
			{TexResolution >> 2,TexResolution >> 2},
			{TexResolution >> 4,TexResolution >> 4}
		};

		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		for (int i = 0; i < CascadeShadow; i++)
		{
			//�V���h�E�}�b�v�����p�̃����_�����O�^�[�Q�b�g�����
			//�e�N�X�`���̃t�H�[�}�b�g��R�����݂̂�32�r�b�g��float�^
			m_shadowMapRT[i].Create
			(
				wh[i][0],
				wh[i][1],
				1,
				1,
				DXGI_FORMAT_R32_FLOAT,
				DXGI_FORMAT_D32_FLOAT,
				clearColor
			);
			//�萔�o�b�t�@���쐬
			m_shadowCb.Init(sizeof(m_shadowCbEntity),&m_shadowCbEntity);
		}
	}

	void ShadowMap::Update(Vector3 lightCameraPos, Vector3 lightCameraTarget)
	{
		//���C�g�̕������v�Z����
		lightDir = lightCameraTarget - lightCameraPos;
		const float DistBoundary = 0.0001f;		//�������E�̋��E
		if (lightDir.Length() < DistBoundary)
		{
			//���C�g�J�����̒����_�Ǝ��_���߂�����
			//�����Ƌ����𗣂��Ă�������
			std::abort();
		}

		//���K�����ĕ����x�N�g���ɕϊ�����
		lightDir.Normalize();

		//���C�g�̕����ɂ���āA���C�g�J�����̏���������߂�
		Vector3 lightCameraUpAxis = Vector3::Up;
		const float UpBoundary = 0.99998f;		//�^�ォ�ǂ����̋��E
		if (fabsf(lightDir.y) > UpBoundary)
		{
			//�قڐ^��or�^���������Ă���
			lightCameraUpAxis = Vector3::AxisX;
			lightCameraUpAxis.Cross(lightDir, Vector3::Right);
		}
		else
		{
			//�^��������Ă��Ȃ�
			lightCameraUpAxis = Vector3::AxisY;
			lightCameraUpAxis = Cross(lightDir, Vector3::Up);
		}

		//���C�g�̉E����
		Vector3 lightViewRight = Vector3::Right;
		lightViewRight.Cross(lightCameraUpAxis, lightDir);
		//���K��
		lightViewRight.Normalize();

		//���C�g�r���[�̉�]
		Matrix lightViewRot;
		//���C�g�r���[�̉���ݒ肷��
		lightViewRot.m[0][0] = lightViewRight.x;
		lightViewRot.m[0][1] = lightViewRight.y;
		lightViewRot.m[0][2] = lightViewRight.z;
		lightViewRot.m[0][3] = 0.0f;
		//���C�g�r���[�̏��ݒ肷��
		lightViewRot.m[1][0] = lightCameraUpAxis.x;
		lightViewRot.m[1][1] = lightCameraUpAxis.y;
		lightViewRot.m[1][2] = lightCameraUpAxis.z;
		lightViewRot.m[1][3] = 0.0f;
		//���C�g�r���[�̑O��ݒ肷��
		lightViewRot.m[2][0] = lightDir.x;
		lightViewRot.m[2][1] = lightDir.y;
		lightViewRot.m[2][2] = lightDir.z;
		lightViewRot.m[2][3] = 0.0f;

		//�V���h�E�}�b�v��ݒ肷��͈�
		float shadowAreaTbl[] = {
			m_range.x,
			m_range.y,
			m_range.z
		};

		//���C�g�r���[�̍������v�Z
		float lightHeight = g_camera3D->GetTarget().y + m_lightHeight;
		
		//�ߕ��ʂ̋���
		float nearPlaneZ = InitNearPlane;
		//�����ʂ̋���
		float farPlaneZ = shadowAreaTbl[0];

		//�J�����̏����
		Vector3 cameraUp = Vector3::Up;
		cameraUp = g_camera3D->GetUp();
		//�J�����̑O����
		Vector3 cameraForward = Vector3::Front;
		cameraForward = g_camera3D->GetForward();
		//�J�����̉E����
		Vector3 cameraRight = Vector3::Right;
		cameraRight = g_camera3D->GetRight();
		//�J�����̈ʒu
		Vector3 cameraPos = Vector3::Zero;
		cameraPos = g_camera3D->GetPosition();

		//�J�X�P�[�h�V���h�E�̖�������
		for (int i = 0; i < CascadeShadow; i++)
		{
			farPlaneZ = nearPlaneZ + shadowAreaTbl[i];
			
			//���C�g�r���[�s��
			for (int i = 0; i < CascadeShadow; i++)
			{
				m_lightViewMatrix[i] = Matrix::Identity;
			}
			//��p�̔������擾
			float halfViewAngle = g_camera3D->GetViewAngle() * 0.5f;
			//�������8���_�����C�g��Ԃɕϊ����āA���ˉe�̕��ƍ��������߂�
			float w, h = 0.0f;
			float far_z = -1.0f;
			Vector3 v[8] = { Vector3::Zero };
			
			{
				//��p���狗���ɑ΂��鍂���̊������v�Z
				float t = tan(halfViewAngle);

				Vector3 toUpperNear, toUpperFar;
				toUpperNear = cameraUp * t * nearPlaneZ;
				toUpperNear.y = min(toUpperNear.y, maxheight);
				toUpperFar = cameraUp * t * farPlaneZ;
				toUpperFar.y = min(toUpperFar.y, maxheight);
				t *= g_camera3D->GetAspect();

				//�ߕ��ʂ̒������W���v�Z
				auto nearPlaneCenterPos = cameraPos + cameraForward * nearPlaneZ;
				//��O�E��̍��W
				v[0] = nearPlaneCenterPos + cameraRight * t * nearPlaneZ + toUpperNear;
				//��O�E���̍��W
				v[1] = v[0] - toUpperNear * 2.0f;
				//��O����̍��W
				v[2] = nearPlaneCenterPos + cameraRight * -t * nearPlaneZ + toUpperNear;
				//��O�����̍��W
				v[3] = v[2] - toUpperNear * 2.0f;

				//�����ʂ̒������W���v�Z
				auto farPlaneCenterPos = cameraPos + cameraForward * farPlaneZ;
				//���E��̍��W
				v[4] = farPlaneCenterPos + cameraRight * t * farPlaneZ + toUpperFar;
				//���E���̍��W
				v[5] = v[4] - toUpperFar * 2.0f;
				//������̍��W
				v[6] = farPlaneCenterPos + cameraRight * -t * farPlaneZ + toUpperFar;
				//�������̍��W
				v[7] = v[6] - toUpperFar * 2.0f;

				//���C�g�s����쐬
				auto viewFrustumCenterPosition = (nearPlaneCenterPos + farPlaneCenterPos) * 0.5f;
				auto lightPos = CalcLightPosition(lightHeight, viewFrustumCenterPosition);

				m_lightViewMatrix[i] = lightViewRot;

				m_lightViewMatrix[i].m[3][0] = lightPos.x;
				m_lightViewMatrix[i].m[3][1] = lightPos.y;
				m_lightViewMatrix[i].m[3][2] = lightPos.z;
				m_lightViewMatrix[i].m[3][3] = 1.0f;

				//���C�g�r���[����
				m_lightViewMatrix[i].Inverse(m_lightViewMatrix[i]);

				//��������\������8���_���v�Z�ł����̂ŁA���C�g��Ԃɍ��W��ϊ����āAAABB�����߂�
				Vector3 vMax = { -FLT_MAX,-FLT_MAX,-FLT_MAX };
				Vector3 vMin = { FLT_MAX, FLT_MAX, FLT_MAX };
				for (auto& vInLight : v)
				{
					//�x�N�g���ƍs��̏�Z
					m_lightViewMatrix[i].Mul(vInLight);
					
					//�ő�l��ݒ�
					vMax.Max(vInLight);
					//�ŏ��l��ݒ�
					vMin.Min(vInLight);
				}
				w = vMax.x - vMin.x;
				h = vMax.y - vMin.y;
				far_z = vMax.z;
			}

			Matrix proj = Matrix::Identity;
			proj.MakeOrthoProjectionMatrix(
				w,
				h,
				far_z / 100.0f,
				far_z
			);
			Matrix m_mat = Matrix::Identity;
			m_lightProMatrix[i].Multiply(m_lightViewMatrix[i], proj);
			m_shadowCbEntity.mLVP[i] = m_lightProMatrix[i];
			m_shadowCbEntity.shadowAreaDepthInViewSpace[i] = farPlaneZ * 0.9f;
			nearPlaneZ = farPlaneZ * 0.85f;		//�M���M�����Ƌ��E�����ł���
		}
	}

	void ShadowMap::RenderToShadowMap()
	{
		auto RenCon = g_graphicsEngine->GetRenderContext();
		for (int i = 0; i < CascadeShadow; i++)
		{
			ShadowTextureNum = i;
			//�����_�����O�^�[�Q�b�g��؂�ւ���
			RenCon.SetRenderTarget(m_shadowMapRT[i].GetRTVCpuDescriptorHandle(), m_shadowMapRT[i].GetDSVCpuDescriptorHandle());

			//�V���h�E�}�b�v���N���A
			float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
			RenCon.ClearRenderTargetView(m_shadowMapRT[i].GetRTVCpuDescriptorHandle(), clearColor);

			for (auto& caster : m_shadowCasters)
			{
				caster->Draw(
					RenCon,
					Matrix::Identity,
					m_lightProMatrix[i]
				);
			}
		}

		//�V���h�E�L���X�^�[���N���A
		m_shadowCasters.clear();
		//�����_�[�^�[�Q�b�g�ƃr���[�|�[�g�����Ƃɖ߂�
		RenCon.SetRenderTarget(g_graphicsEngine->GetCurrentFrameBuffuerRTV(), g_graphicsEngine->GetCurrentFrameBuffuerDSV());
	}
}