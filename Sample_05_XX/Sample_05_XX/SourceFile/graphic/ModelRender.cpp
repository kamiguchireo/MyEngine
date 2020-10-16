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
			InitData.m_expandConstantBuffer = m_expandConstantBuffer;
			InitData.m_expandConstantBufferSize = (sizeof(m_expandConstantBuffer));
			InitData.m_expandShaderResoruceView = m_expandShaderResoruceView;

			m_model.Init(InitData);
			RC = g_graphicsEngine->GetRenderContext();
			return true;
		}

		void ModelRender::Update()
		{
			m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
		}

		void ModelRender::Draw()
		{
			m_model.Draw(RC);
		}
	}
}