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
		//スケールと位置をセット
		m_skyModel->SetScale(m_scale);
		m_skyModel->SetPosition(m_pos);
		//シャドウは適用しない
		m_skyModel->SetShadowCasterFlag(false);
		m_skyModel->SetShadowRecieverFlag(false);
		//ファイルパスセット
		m_skyModel->SetTkmFilePath("Assets/modelData/SkyCube.tkm");
		//シェーダーのファイルパスをセット
		m_skyModel->SetfxFilePath("Assets/shader/SkyCube.fx");
		//ピクセルシェーダーのエントリーポイントを設定
		m_skyModel->SetPSEntryPoint("PSMain");
		return true;
	}

	void Sky::Update()
	{
		m_skyModel->SetPosition(m_pos);
	}
}