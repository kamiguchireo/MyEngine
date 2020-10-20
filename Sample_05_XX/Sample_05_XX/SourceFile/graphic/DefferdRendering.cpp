#include "stdafx.h"
#include "DefferdRendering.h"

namespace Engine {
	DefferdRendering::DefferdRendering()
	{

	}

	DefferdRendering::~DefferdRendering()
	{

	}

	void DefferdRendering::CreateRT()
	{
		//�A���x�h�p�̃����_�[�^�[�Q�b�g�̍쐬
		albedRT.Create(
			FRAME_BUFFER_W, FRAME_BUFFER_H,
			1, 1,
			DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT
		);
		//�@���p�̃����_�[�^�[�Q�b�g�̍쐬
		normalRT.Create(
			FRAME_BUFFER_W, FRAME_BUFFER_H,
			1, 1,
			DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_UNKNOWN
		);
		SpriteInitData initData;
		initData.m_width = FRAME_BUFFER_W;
		initData.m_height = FRAME_BUFFER_H;

		initData.m_textures[0] = &albedRT.GetRenderTargetTexture();
		initData.m_textures[1] = &normalRT.GetRenderTargetTexture();
		initData.m_fxFilePath = "Assets/shader/sprite.fx";
		initData.m_psEntryPoinFunc = "PSDefferd";
		defferdLightingSprite.Init(initData);
	}

	void DefferdRendering::DrawRT()
	{
		RenderTarget* rts[] = {
			&albedRT,
			&normalRT,
		};
		auto& RenCon = g_graphicsEngine->GetRenderContext();
		RenCon.WaitUntilToPossibleSetRenderTargets(TexNum, rts);
		RenCon.SetRenderTargets(TexNum, rts);
		RenCon.ClearRenderTargetViews(TexNum, rts);
		for (const auto& caster : m_Casters)
		{
			caster->Draw(RenCon);
		}

		//�L���X�^�[���N���A
		m_Casters.clear();
		RenCon.WaitUntilFinishDrawingToRenderTargets(TexNum, rts);

		//�����_�����O����t���[���o�b�t�@�ɖ߂�
		g_graphicsEngine->ChangeRenderTargetToFrameBuffer(RenCon);
		defferdLightingSprite.Update(Vector3::Zero, Quaternion::Identity, Vector3::One);
		defferdLightingSprite.Draw(RenCon);
	}
}