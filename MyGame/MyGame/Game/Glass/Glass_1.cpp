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
	m_Glass.Init(m_InitData);
	
	return true;
}

void Glass_1::Update()
{
	m_Glass.UpdateWorldMatrix(Vector3::Zero, Quaternion::Identity, Vector3::One);
}

void Glass_1::Draw()
{
	auto& RenCon = g_graphicsEngine->GetRenderContext();
	m_Glass.Draw(RenCon);
}