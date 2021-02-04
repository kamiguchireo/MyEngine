#include "stdafx.h"
#include "Tree2.h"

Tree2::Tree2()
{

}

Tree2::~Tree2()
{

}

bool Tree2::Start()
{
	m_InitData.m_tkmFilePath = "Assets/modelData/SM_Tree_Tropic_02.tkm";
	m_InitData.m_vsEntryPointFunc = "VSMainInstancing";
	m_InitData.m_psEntryPointFunc = "PSMain";
	m_InitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	m_Tree.Init(m_InitData, m_instanceNum);
	m_Tree.SetShadowRecieverFlag(true);

	return true;
}

void Tree2::Update()
{
	m_Tree.Refresh();

	//インスタンシング描画
	for (auto& objData : m_renderObjDatas)
	{
		m_Tree.UpdateInstancingData(objData.position, objData.rotation, objData.scale);
	}
	m_Tree.UpdateInstancingSTB();
	//g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_Tree);
}

void Tree2::Draw()
{
	auto& RenCon = g_graphicsEngine->GetRenderContext();
	m_Tree.Draw(RenCon);
}