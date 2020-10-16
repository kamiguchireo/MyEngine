#include "stdafx.h"
#include "DefferdRendering.h"

DefferdRendering::DefferdRendering()
{

}

DefferdRendering::~DefferdRendering()
{

}

void DefferdRendering::CreateRT()
{
	albedRT.Create(
		FRAME_BUFFER_W, FRAME_BUFFER_H,
		1, 1,
		DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT
	);
	initData.m_width = FRAME_BUFFER_W;
	initData.m_height = FRAME_BUFFER_H;
	initData.m_textures[0] = &albedRT.GetRenderTargetTexture();
	initData.m_fxFilePath = "Assets/shader/sprite.fx";

	defferdLightingSprite.Init(initData);
}

void DefferdRendering::DrawRT()
{
	RenderTarget* rts[] = {
		&albedRT
	};
	auto& RenCon = g_graphicsEngine->GetRenderContext();
	RenCon.WaitUntilToPossibleSetRenderTargets(TexNum, rts);
	RenCon.SetRenderTargets(TexNum, rts);
	RenCon.ClearRenderTargetViews(TexNum, rts);
	for (const auto& caster : m_Casters)
	{
		caster->Draw(RenCon);
	}
	RenCon.WaitUntilFinishDrawingToRenderTargets(TexNum, rts);

	//レンダリング先をフレームバッファに戻す
	g_graphicsEngine->ChangeRenderTargetToFrameBuffer(RenCon);
	defferdLightingSprite.Draw(RenCon);
}