#pragma once
#include "RenderTarget.h"
#include "SourceFile/NonCopyable.h"
#include "Model.h"

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

		//�V���h�E�}�b�v�ɉe���������ރ^�C�~���O�ŌĂ�ł�������
		void RenderToShadowMap();

		//�V���h�E�L���X�^�[��o�^
		//RenderToShadowMap���Ăяo������o�^�������X�g�̓N���A�����
		//��ɉe���o�����������疈�t���[���Ă�ł�������
		void RegistShadowCaster(Model* shadowCaster)
		{
			m_shadowCasters.push_back(shadowCaster);
		}

		void SendShadowRecieverParamToGpu();

		Texture& GetSRV(int i)
		{
			return m_shadowMapRT[i].GetRenderTargetTexture();
		}

		ConstantBuffer& GetConstantBuffer()
		{
			return m_shadowCb;
		}
	private:
		//���C�g�̍��W���v�Z����B
		// �������ꂽ��������ʂ����C�g�̍��W���v�Z���܂��B
		// ���C�g�̍��W�̌v�Z�̓��C�g�̍����A���C�g�̕����A�����āA
		// ������̒��S���W(�ߕ��ʂ̒��S���W�Ɖ����ʂ̒��S���W�����񂾐����̒��_���W)
		// ����v�Z����܂��B
		// �@�@���m�����ɂ��Ă̈ꎟ�������������܂��B
		// ���C�g�̍��� = ������̒��S���W.y + ���C�g�̕���.y * ��
		// �� = ( ���C�g�̍��� - ������̒��S���W.y ) / ���C�g�̕���.y
		// �A�@�����g���āA���C�g�̍��W�����߂�B
		// ���C�g�̍��W = ������̒��S���W + ���C�g�̕��� * ��
		//lightHeight		���C�g�̍����B
		//viewFrustomCenterPosition		�������ꂽ������̒��S���W�B
		// �v�Z���ꂽ���C�g�̍��W
		Vector3 CalcLightPosition(float lightHeight, Vector3 viewFrustomCenterPosition);

	private:
		struct SShadowCb {
			Matrix mLVP[3];
			float shadowAreaDepthInViewSpace[3];	//�J������Ԃł̉e�𗎂Ƃ��G���A�̐[�x�e�[�u���B
		};
		const int TexResolutionW = 2560;		//�V���h�E�}�b�v�e�N�X�`���̉𑜓x
		const int TexResolutionH = 1440;		//�V���h�E�}�b�v�e�N�X�`���̉𑜓x

		RenderTarget m_shadowMapRT[3];
		ConstantBuffer m_shadowCb;		//�e�𗎂Ƃ����Ɏg�p����萔�o�b�t�@
		SShadowCb m_shadowCbEntity;
		Vector3 m_range = { 500.0f,1000.0f,2000.0f };		//�V���h�E�}�b�v��ݒ肷��͈�
		float m_lightHeight = 1000.0f;				//���C�g�̍����B
		Matrix m_lightProMatrix[3] = { Matrix::Identity };
		float maxheight = 1000.0f;		//�e�Ɋ܂߂�ő�̍���
		Vector3 lightDir = Vector3::Down;
		std::vector<Model*> m_shadowCasters;		//�V���h�E�L���X�^�[�̔z��
		ModelInitData InitData;
		bool ResourceInited[3] = {false};
	};
}