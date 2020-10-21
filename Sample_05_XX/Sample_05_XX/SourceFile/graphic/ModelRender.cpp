#include "stdafx.h"
#include "ModelRender.h"

namespace Engine {
	namespace prefab {
		ModelRender::ModelRender()
		{
			//ライトを用意する。
			light.directionalLight[0].color.x = 1.0f;
			light.directionalLight[0].color.y = 1.0f;
			light.directionalLight[0].color.z = 1.0f;

			light.directionalLight[0].direction.x = 1.0f;
			light.directionalLight[0].direction.y = 0.0f;
			light.directionalLight[0].direction.z = 0.0f;

			light.ambinetLight.x = 1.0f;
			light.ambinetLight.y = 1.0f;
			light.ambinetLight.z = 1.0f;
			light.eyePos = g_camera3D->GetPosition();
			light.specPow = 5.0f;
		}

		ModelRender::~ModelRender()
		{

		}

		bool ModelRender::Start()
		{
			if (m_tkmFilePath == nullptr)
			{
				std::abort();
				//ファイルパスをセットしてください。
			}
			InitData.m_tkmFilePath = m_tkmFilePath;
			InitData.m_vsEntryPointFunc = m_vsEntryPointFunc;
			InitData.m_psEntryPointFunc = m_psEntryPointFunc;
			InitData.m_fxFilePath = m_fxFilePath;
			InitData.m_expandConstantBuffer = &light;
			InitData.m_expandConstantBufferSize = (sizeof(light));
			InitData.m_expandShaderResoruceView = m_expandShaderResoruceView;

			//スケルトンがセットされているとき
			if (SkeletonFlag == true)
			{
				m_model.BindSkeleton(*m_skeleton);
			}
			m_model.Init(InitData);
			RC = g_graphicsEngine->GetRenderContext();
			return true;
		}

		void ModelRender::Update()
		{
			//スケルトンがセットされているとき
			if (SkeletonFlag == true)
			{
				m_skeleton->Update(m_model.GetWorldMatrix());
			}
			m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
			g_graphicsEngine->GetDefferdRendering()->RegistCaster(&m_model);
		}

		void ModelRender::Draw()
		{
			m_model.Draw(RC);
		}
	}
}