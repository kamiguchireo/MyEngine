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
			//シャドウマップ生成用のレンダリングターゲットを作る
			//テクスチャのフォーマットはR成分のみの32ビットのfloat型
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
			//定数バッファを作成
			m_shadowCb.Init(sizeof(m_shadowCbEntity),&m_shadowCbEntity);
		}
	}

	void ShadowMap::Update(Vector3 lightCameraPos, Vector3 lightCameraTarget)
	{
		//ライトの方向を計算する
		lightDir = lightCameraTarget - lightCameraPos;
		const float DistBoundary = 0.0001f;		//距離限界の境界
		if (lightDir.Length() < DistBoundary)
		{
			//ライトカメラの注視点と視点が近すぎる
			//もっと距離を離してください
			std::abort();
		}

		//正規化して方向ベクトルに変換する
		lightDir.Normalize();

		//ライトの方向によって、ライトカメラの上方向を決める
		Vector3 lightCameraUpAxis = Vector3::Up;
		const float UpBoundary = 0.99998f;		//真上かどうかの境界
		if (fabsf(lightDir.y) > UpBoundary)
		{
			//ほぼ真上or真下を向いている
			lightCameraUpAxis = Vector3::AxisX;
			lightCameraUpAxis.Cross(lightDir, Vector3::Right);
		}
		else
		{
			//真上を向いていない
			lightCameraUpAxis = Vector3::AxisY;
			lightCameraUpAxis = Cross(lightDir, Vector3::Up);
		}

		//ライトの右方向
		Vector3 lightViewRight = Vector3::Right;
		lightViewRight.Cross(lightCameraUpAxis, lightDir);
		//正規化
		lightViewRight.Normalize();

		//ライトビューの回転
		Matrix lightViewRot;
		//ライトビューの横を設定する
		lightViewRot.m[0][0] = lightViewRight.x;
		lightViewRot.m[0][1] = lightViewRight.y;
		lightViewRot.m[0][2] = lightViewRight.z;
		lightViewRot.m[0][3] = 0.0f;
		//ライトビューの上を設定する
		lightViewRot.m[1][0] = lightCameraUpAxis.x;
		lightViewRot.m[1][1] = lightCameraUpAxis.y;
		lightViewRot.m[1][2] = lightCameraUpAxis.z;
		lightViewRot.m[1][3] = 0.0f;
		//ライトビューの前を設定する
		lightViewRot.m[2][0] = lightDir.x;
		lightViewRot.m[2][1] = lightDir.y;
		lightViewRot.m[2][2] = lightDir.z;
		lightViewRot.m[2][3] = 0.0f;

		//シャドウマップを設定する範囲
		float shadowAreaTbl[] = {
			m_range.x,
			m_range.y,
			m_range.z
		};

		//ライトビューの高さを計算
		float lightHeight = g_camera3D->GetTarget().y + m_lightHeight;
		
		//近平面の距離
		float nearPlaneZ = InitNearPlane;
		//遠平面の距離
		float farPlaneZ = shadowAreaTbl[0];

		//カメラの上方向
		Vector3 cameraUp = Vector3::Up;
		cameraUp = g_camera3D->GetUp();
		//カメラの前方向
		Vector3 cameraForward = Vector3::Front;
		cameraForward = g_camera3D->GetForward();
		//カメラの右方向
		Vector3 cameraRight = Vector3::Right;
		cameraRight = g_camera3D->GetRight();
		//カメラの位置
		Vector3 cameraPos = Vector3::Zero;
		cameraPos = g_camera3D->GetPosition();

		//カスケードシャドウの枚数分回す
		for (int i = 0; i < CascadeShadow; i++)
		{
			farPlaneZ = nearPlaneZ + shadowAreaTbl[i];
			
			//ライトビュー行列
			for (int i = 0; i < CascadeShadow; i++)
			{
				m_lightViewMatrix[i] = Matrix::Identity;
			}
			//画角の半分を取得
			float halfViewAngle = g_camera3D->GetViewAngle() * 0.5f;
			//視推台の8頂点をライト空間に変換して、正射影の幅と高さを求める
			float w, h = 0.0f;
			float far_z = -1.0f;
			Vector3 v[8] = { Vector3::Zero };
			
			{
				//画角から距離に対する高さの割合を計算
				float t = tan(halfViewAngle);

				Vector3 toUpperNear, toUpperFar;
				toUpperNear = cameraUp * t * nearPlaneZ;
				toUpperNear.y = min(toUpperNear.y, maxheight);
				toUpperFar = cameraUp * t * farPlaneZ;
				toUpperFar.y = min(toUpperFar.y, maxheight);
				t *= g_camera3D->GetAspect();

				//近平面の中央座標を計算
				auto nearPlaneCenterPos = cameraPos + cameraForward * nearPlaneZ;
				//手前右上の座標
				v[0] = nearPlaneCenterPos + cameraRight * t * nearPlaneZ + toUpperNear;
				//手前右下の座標
				v[1] = v[0] - toUpperNear * 2.0f;
				//手前左上の座標
				v[2] = nearPlaneCenterPos + cameraRight * -t * nearPlaneZ + toUpperNear;
				//手前左下の座標
				v[3] = v[2] - toUpperNear * 2.0f;

				//遠平面の中央座標を計算
				auto farPlaneCenterPos = cameraPos + cameraForward * farPlaneZ;
				//奥右上の座標
				v[4] = farPlaneCenterPos + cameraRight * t * farPlaneZ + toUpperFar;
				//奥右下の座標
				v[5] = v[4] - toUpperFar * 2.0f;
				//奥左上の座標
				v[6] = farPlaneCenterPos + cameraRight * -t * farPlaneZ + toUpperFar;
				//奥左下の座標
				v[7] = v[6] - toUpperFar * 2.0f;

				//ライト行列を作成
				auto viewFrustumCenterPosition = (nearPlaneCenterPos + farPlaneCenterPos) * 0.5f;
				auto lightPos = CalcLightPosition(lightHeight, viewFrustumCenterPosition);

				m_lightViewMatrix[i] = lightViewRot;

				m_lightViewMatrix[i].m[3][0] = lightPos.x;
				m_lightViewMatrix[i].m[3][1] = lightPos.y;
				m_lightViewMatrix[i].m[3][2] = lightPos.z;
				m_lightViewMatrix[i].m[3][3] = 1.0f;

				//ライトビュー完成
				m_lightViewMatrix[i].Inverse(m_lightViewMatrix[i]);

				//視推台を構成する8頂点を計算できたので、ライト空間に座標を変換して、AABBを求める
				Vector3 vMax = { -FLT_MAX,-FLT_MAX,-FLT_MAX };
				Vector3 vMin = { FLT_MAX, FLT_MAX, FLT_MAX };
				for (auto& vInLight : v)
				{
					//ベクトルと行列の乗算
					m_lightViewMatrix[i].Mul(vInLight);
					
					//最大値を設定
					vMax.Max(vInLight);
					//最小値を設定
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
			nearPlaneZ = farPlaneZ * 0.85f;		//ギリギリだと境界線ができる
		}
	}

	void ShadowMap::RenderToShadowMap()
	{
		auto RenCon = g_graphicsEngine->GetRenderContext();
		for (int i = 0; i < CascadeShadow; i++)
		{
			ShadowTextureNum = i;
			//レンダリングターゲットを切り替える
			RenCon.SetRenderTarget(m_shadowMapRT[i].GetRTVCpuDescriptorHandle(), m_shadowMapRT[i].GetDSVCpuDescriptorHandle());

			//シャドウマップをクリア
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

		//シャドウキャスターをクリア
		m_shadowCasters.clear();
		//レンダーターゲットとビューポートをもとに戻す
		RenCon.SetRenderTarget(g_graphicsEngine->GetCurrentFrameBuffuerRTV(), g_graphicsEngine->GetCurrentFrameBuffuerDSV());
	}
}