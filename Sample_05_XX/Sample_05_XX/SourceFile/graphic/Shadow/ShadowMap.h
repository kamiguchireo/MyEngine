#pragma once
#include "RenderTarget.h"
namespace Engine {
	class ShadowMap:Engine::Noncopyable
	{
	public:
		ShadowMap();
		~ShadowMap();

		//シャドウマップのレンダーターゲットの作成
		void ShadowMapRTCreate();

		//lightCameraPos		ライトの位置
		//lightCameraTarget		ライトのターゲット
		void Update(Vector3 lightCameraPos, Vector3 lightCameraTarget);

	private:
		struct SShadowCb {
			Matrix mLVP[3];
			float shadowAreaDepthInViewSpace[3];	//カメラ空間での影を落とすエリアの深度テーブル。
		};
		const int TexResolution = 2048;		//シャドウマップテクスチャの解像度
		const int CascadeShadow = 3;		//シャドウマップの枚数
		RenderTarget m_shadowMapRT[3];
		ConstantBuffer m_shadowCb;		//影を落とす時に使用する定数バッファ
		SShadowCb m_shadowCbEntity;
	};
}