#include "stdafx.h"
#include "ModelRender.h"

namespace Engine {
	namespace prefab {
		ModelRender::ModelRender()
		{

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
			InitData.m_expandShaderResoruceView = m_expandShaderResoruceView;

			//スケルトンがセットされているとき
			if (m_skeleton != nullptr)
			{
				m_model.BindSkeleton(*m_skeleton);
			}

			m_model.Init(InitData, m_numInstance);
			return true;
		}

		void ModelRender::Update()
		{
			auto& RC = g_graphicsEngine->GetRenderContext();
			if (UpdateFlag)
			{
				m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
			}

			//スケルトンがセットされているとき
			if (m_skeleton != nullptr)
			{
				m_skeleton->Update(m_model.GetWorldMatrix());
			}
			//シャドウキャスターに登録されているとき
			if (m_ShadowCasterFlag == true)
			{
				g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
			}
			g_graphicsEngine->GetDefferdRendering()->RegistCaster(&m_model);
		}

		void ModelRender::Draw()
		{

		}
	}
}