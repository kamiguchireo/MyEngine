#include "stdafx.h"
#include "Sky.h"
#include "Material.h"

namespace Engine {
	Sky::Sky()
	{
		if (m_tex == nullptr)
		{
			m_tex = std::make_unique<Texture>();
		}
	}

	Sky::~Sky()
	{

	}

	bool Sky::Init()
	{
		m_skyModel = NewGO<prefab::ModelRender>(0);
		//スケールと位置をセット
		m_scale *= 1000.0f;
		m_skyModel->SetScale(m_scale);
		m_skyModel->SetPosition(m_pos);
		//シャドウは適用しない
		m_skyModel->SetShadowCasterFlag(false);
		m_skyModel->SetShadowRecieverFlag(false);
		m_skyModel->SetIsDefferd(false);
		//ファイルパスセット
		m_skyModel->SetTkmFilePath("Assets/modelData/SkyCube.tkm");
		//シェーダーのファイルパスをセット
		m_skyModel->SetfxFilePath("Assets/shader/SkyCube.fx");
		//ピクセルシェーダーのエントリーポイントを設定
		m_skyModel->SetPSEntryPoint("PSMain");
		m_skyModel->Start();
		//m_tex->InitFromDDSFile(L"Assets/modelData/skyCubeMap.dds");
		////テクスチャ差し替え
		//auto meshs = m_skyModel->GetModel().GetMeshParts().GetMeshs();
		//for (auto mesh : meshs)
		//{
		//	for (auto mat : mesh->m_materials)
		//	{
		//		mat->SetDiffuseTexture(m_tex->Get());
		//	}
		//}
		return true;
	}

	void Sky::Update()
	{
		m_skyModel->SetPosition(m_pos);
		m_skyModel->SetScale(m_scale);

	}
}