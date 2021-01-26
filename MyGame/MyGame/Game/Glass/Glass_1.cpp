#include "stdafx.h"
#include "Glass_1.h"

Glass_1::Glass_1()
{

}

Glass_1::~Glass_1()
{

}

bool Glass_1::Start()
{
	m_InitData.m_tkmFilePath = "Assets/modelData/SM_Grass_1.tkm";
	m_InitData.m_psEntryPointFunc = "PSMain";
	m_InitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	m_Glass.Init(m_InitData,m_instanceNum);
	m_Glass.SetShadowRecieverFlag(false);
	return true;
}

void Glass_1::Update()
{
	m_Glass.Refresh();

	//インスタンシング描画するとき
	if (m_instanceNum > 1)
	{
		for (auto& objData : m_renderObjDatas) {
			m_Glass.UpdateInstancingData(objData.position, objData.rotation, objData.scale);
		}
	}
	else
	{
		m_Glass.UpdateWorldMatrix({ 0.0f,0.0f,-1200.0f }, Quaternion::Identity, Vector3::One);
	}
	if (m_renderObjDatas.size() > 1) {

		m_Glass.UpdateInstancingSTB();
	}

}

void Glass_1::Draw()
{
	auto& RenCon = g_graphicsEngine->GetRenderContext();
	m_Glass.Draw(RenCon);
}