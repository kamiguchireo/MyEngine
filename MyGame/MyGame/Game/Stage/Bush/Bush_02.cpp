#include "stdafx.h"
#include "Bush_02.h"

Bush_02::Bush_02()
{

}

Bush_02::~Bush_02()
{

}

bool Bush_02::Start()
{
	m_InitData.m_tkmFilePath = "Assets/modelData/SM_BushA_02.tkm";
	m_InitData.m_vsEntryPointFunc = "VSMainInstancing";
	m_InitData.m_psEntryPointFunc = "PSMain";
	m_InitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	m_Bush.Init(m_InitData,m_instanceNum);
	m_Bush.SetShadowRecieverFlag(false);
	
	return true;
}

void Bush_02::Update()
{
	m_Bush.Refresh();

	//インスタンシング描画
	for (auto& objData : m_renderObjDatas) 
	{
		m_Bush.UpdateInstancingData(objData.position, objData.rotation, objData.scale);
	}
	m_Bush.UpdateInstancingSTB();
	//g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_Bush);
}

void Bush_02::Draw()
{
	auto& RenCon = g_graphicsEngine->GetRenderContext();
	m_Bush.Draw(RenCon);
}