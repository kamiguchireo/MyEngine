#pragma once
#include "RenderTarget.h"
namespace Engine {
	class ShadowMap:Engine::Noncopyable
	{
	public:
		ShadowMap();
		~ShadowMap();

		//�V���h�E�}�b�v�̃����_�[�^�[�Q�b�g�̍쐬
		void ShadowMapRTCreate();

		//lightCameraPos		���C�g�̈ʒu
		//lightCameraTarget		���C�g�̃^�[�Q�b�g
		void Update(Vector3 lightCameraPos, Vector3 lightCameraTarget);

	private:
		struct SShadowCb {
			Matrix mLVP[3];
			float shadowAreaDepthInViewSpace[3];	//�J������Ԃł̉e�𗎂Ƃ��G���A�̐[�x�e�[�u���B
		};
		const int TexResolution = 2048;		//�V���h�E�}�b�v�e�N�X�`���̉𑜓x
		const int CascadeShadow = 3;		//�V���h�E�}�b�v�̖���
		RenderTarget m_shadowMapRT[3];
		ConstantBuffer m_shadowCb;		//�e�𗎂Ƃ����Ɏg�p����萔�o�b�t�@
		SShadowCb m_shadowCbEntity;
	};
}