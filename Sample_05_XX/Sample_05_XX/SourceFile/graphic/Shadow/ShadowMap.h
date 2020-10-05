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
		//ライトの座標を計算する。
		// 分割された視推台を写すライトの座標を計算します。
		// ライトの座標の計算はライトの高さ、ライトの方向、そして、
		// 視推台の中心座標(近平面の中心座標と遠平面の中心座標を結んだ線分の中点座標)
		// から計算されます。
		// ①　未知数αについての一次方程式を解きます。
		// ライトの高さ = 視推台の中心座標.y + ライトの方向.y * α
		// α = ( ライトの高さ - 視推台の中心座標.y ) / ライトの方向.y
		// ②　αを使って、ライトの座標を求める。
		// ライトの座標 = 視推台の中心座標 + ライトの方向 * α
		//lightHeight		ライトの高さ。
		//viewFrustomCenterPosition		分割された視推台の中心座標。
		// 計算されたライトの座標
		Vector3 CalcLightPosition(float lightHeight, Vector3 viewFrustomCenterPosition);

	private:
		struct SShadowCb {
			Matrix mLVP[3];
			float shadowAreaDepthInViewSpace[3];	//カメラ空間での影を落とすエリアの深度テーブル。
		};
		const int TexResolution = 2048;		//シャドウマップテクスチャの解像度
		RenderTarget m_shadowMapRT[CascadeShadow];
		ConstantBuffer m_shadowCb;		//影を落とす時に使用する定数バッファ
		SShadowCb m_shadowCbEntity;
		Vector3 m_range = { 500.0f,1000.0f,2000.0f };		//シャドウマップを設定する範囲
		float m_lightHeight = 1000.0f;				//ライトの高さ。
		const float InitNearPlane = 0.0f;		//NearPlaneの初期値
		Matrix m_lightViewMatrix[CascadeShadow] = { Matrix::Identity };
		Matrix m_lightProMatrix[CascadeShadow] = { Matrix::Identity };
		float maxheight = 500.0f;		//影に含める最大の高さ
		Vector3 lightDir = Vector3::Down;
	};
}