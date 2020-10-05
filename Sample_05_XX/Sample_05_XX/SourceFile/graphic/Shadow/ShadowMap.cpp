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
				0,
				1,
				DXGI_FORMAT_R32_FLOAT,
				DXGI_FORMAT_R32_FLOAT,
				clearColor
			);
			//�萔�o�b�t�@���쐬
			m_shadowCb.Init(sizeof(m_shadowCbEntity),&m_shadowCbEntity);
		}
	}

	void ShadowMap::Update(Vector3 lightCameraPos, Vector3 lightCameraTarget)
	{

	}
}