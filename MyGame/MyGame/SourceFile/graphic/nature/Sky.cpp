#include "stdafx.h"
#include "Sky.h"

namespace Engine {
	namespace prefab {
		Sky::Sky()
		{

		}

		Sky::~Sky()
		{
			if (m_skyModel != nullptr)
			{
				DeleteGO(m_skyModel);
			}
		}

		bool Sky::Start()
		{
			m_skyModel = NewGO<ModelRender>(0);
			//スケールと位置をセット
			m_skyModel->SetScale(m_scale);
			m_skyModel->SetPosition(m_pos);
			//シャドウは適用しない
			m_skyModel->SetShadowCasterFlag(false);
			m_skyModel->SetShadowRecieverFlag(false);
			//ファイルパスセット
			m_skyModel->SetTkmFilePath("Assets/modelData/SkyCube.tkm");

			return true;
		}

	}
}