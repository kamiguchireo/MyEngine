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
				//�t�@�C���p�X���Z�b�g���Ă��������B
			}
			InitData.m_tkmFilePath = m_tkmFilePath;
			InitData.m_vsEntryPointFunc = m_vsEntryPointFunc;
			InitData.m_psEntryPointFunc = m_psEntryPointFunc;
			InitData.m_fxFilePath = m_fxFilePath;
			InitData.m_expandShaderResoruceView = m_expandShaderResoruceView;

			//�X�P���g�����Z�b�g����Ă���Ƃ�
			if (m_skeleton != nullptr)
			{
				m_model.BindSkeleton(*m_skeleton);
			}
			m_model.Init(InitData);
			//auto RC = g_graphicsEngine->GetRenderContext();
			return true;
		}

		void ModelRender::Update()
		{
			//�X�P���g�����Z�b�g����Ă���Ƃ�
			if (m_skeleton != nullptr)
			{
				m_skeleton->Update(m_model.GetWorldMatrix());
			}
			//�V���h�E�L���X�^�[�ɓo�^����Ă���Ƃ�
			if (m_ShadowCasterFlag == true)
			{
				g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
			}
			m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);

			g_graphicsEngine->GetDefferdRendering()->RegistCaster(&m_model);

		}
		//void ModelRender::Draw()
		//{
		//	m_model.Draw(RC);
		//}
	}
}