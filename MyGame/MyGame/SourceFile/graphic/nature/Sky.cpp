#include "stdafx.h"
#include "Sky.h"

namespace Engine {
	Sky::Sky()
	{

	}

	Sky::~Sky()
	{

	}

	bool Sky::Init()
	{
		m_skyModel = NewGO<prefab::ModelRender>(0);
		//�X�P�[���ƈʒu���Z�b�g
		m_skyModel->SetScale(m_scale);
		m_skyModel->SetPosition(m_pos);
		//�V���h�E�͓K�p���Ȃ�
		m_skyModel->SetShadowCasterFlag(false);
		m_skyModel->SetShadowRecieverFlag(false);
		//�t�@�C���p�X�Z�b�g
		m_skyModel->SetTkmFilePath("Assets/modelData/SkyCube.tkm");
		//�V�F�[�_�[�̃t�@�C���p�X���Z�b�g
		m_skyModel->SetfxFilePath("Assets/shader/SkyCube.fx");
		//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g��ݒ�
		m_skyModel->SetPSEntryPoint("PSMain");
		return true;
	}

	void Sky::Update()
	{
		m_skyModel->SetPosition(m_pos);
	}
}