#include "stdafx.h"
#include "Grass_03.h"

Grass_03::Grass_03()
{

}

Grass_03::~Grass_03()
{

}

bool Grass_03::Start()
{
	m_InitData.m_tkmFilePath = "Assets/modelData/SM_Grass_03.tkm";
	m_InitData.m_vsEntryPointFunc = "VSMainInstancing";
	m_InitData.m_psEntryPointFunc = "PSMain";
	m_InitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	m_Glass.Init(m_InitData,m_instanceNum);
	m_Glass.SetShadowRecieverFlag(false);
	
	return true;
}

void Grass_03::Update()
{
	m_Glass.Refresh();

	//インスタンシング描画
	for (auto& objData : m_renderObjDatas) 
	{
		m_Glass.UpdateInstancingData(objData.position, objData.rotation, objData.scale);
	}
	m_Glass.UpdateInstancingSTB();
}

void Grass_03::Draw()
{
	auto& RenCon = g_graphicsEngine->GetRenderContext();
	m_Glass.Draw(RenCon);
}