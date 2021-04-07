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

		//シャドウマップのレンダーターゲットの作成
		void ShadowMapRTCreate();

		//lightCameraPos		ライトの位置
		//lightCameraTarget		ライトのターゲット
		void Update();

		//シャドウマップに影を書き込むタイミングで呼んでください
		void RenderToShadowMap();

		//シャドウキャスターを登録
		//RenderToShadowMapを呼び出したら登録したリストはクリアされる
		//常に影を出したかったら毎フレーム呼んでください
		void RegistShadowCaster(Model* shadowCaster)
		{
			m_shadowCasters.push_back(shadowCaster);
		}

		void SendShadowRecieverParamToGpu();

		Texture& GetSRV(int i)
		{
			return m_shadowMapRT[i]->GetRenderTargetTexture();
		}

		std::unique_ptr<ConstantBuffer>& GetConstantBuffer()
		{
			return m_shadowCb;
		}

		void SetLigPos(Vector3 pos)
		{
			ligPos = pos;
		}

		void SetLigTarget(Vector3 pos)
		{
			ligTarget = pos;
		}
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
			Matrix mLVP[3] = {Matrix::Identity};
			float shadowAreaDepthInViewSpace[3] = { 500.0f,1000.0f,2000.0f };	//カメラ空間での影を落とすエリアの深度テーブル。
		};
		std::unique_ptr<RenderTarget> m_shadowMapRT[3];
		std::unique_ptr<ConstantBuffer> m_shadowCb;		//影を落とす時に使用する定数バッファ
		SShadowCb m_shadowCbEntity;
		Vector3 m_range = { 500.0f,1000.0f,2000.0f };		//シャドウマップを設定する範囲
		float m_lightHeight = 1000.0f;				//ライトの高さ。
		Matrix m_lightProMatrix[3] = { Matrix::Identity };
		float maxheight = 1000.0f;		//影に含める最大の高さ
		Vector3 lightDir = Vector3::Down;
		std::vector<Model*> m_shadowCasters;		//シャドウキャスターの配列
		ModelInitData InitData;
		bool ResourceInited[3] = {false};
		Vector3 ligPos = Vector3::Zero;
		Vector3 ligTarget = { 1.0f,-1.0f,-1.0f };
	};
}