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
			//�X�P�[���ƈʒu���Z�b�g
			m_skyModel->SetScale(m_scale);
			m_skyModel->SetPosition(m_pos);
			//�V���h�E�͓K�p���Ȃ�
			m_skyModel->SetShadowCasterFlag(false);
			m_skyModel->SetShadowRecieverFlag(false);
			//�t�@�C���p�X�Z�b�g
			m_skyModel->SetTkmFilePath("Assets/modelData/SkyCube.tkm");

			return true;
		}

	}
}