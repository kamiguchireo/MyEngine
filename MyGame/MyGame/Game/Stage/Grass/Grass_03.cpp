#include "stdafx.h"
#include "Grass_03.h"

Grass_03::Grass_03()
{

}

Grass_03::~Grass_03()
{

}

void Grass_03::Destroy()
{
	if (m_Glass != nullptr)
	{
		DeleteGO(m_Glass);
		m_Glass = nullptr;
	}
}

bool Grass_03::Start()
{
	m_Glass = NewGO<prefab::ModelRender>(1);
	m_Glass->SetTkmFilePath("Assets/modelData/SM_Grass_03.tkm");
	m_Glass->SetVSEntryPoint("VSMainInstancing");
	m_Glass->SetPSEntryPoint("PSMain");
	m_Glass->SetfxFilePath("Assets/shader/NoAnimModel_LambertSpecularAmbient.fx");
	m_Glass->SetInstanceNum(m_instanceNum);
	m_Glass->SetShadowRecieverFlag(false);
	m_Glass->SetShadowCasterFlag(false);
	m_Glass->SetIsDefferd(false);
	
	return true;
}

void Grass_03::Update()
{
	m_Glass->ModelInstanceRefresh();

	//インスタンシング描画
	for (auto& objData : m_renderObjDatas) 
	{
		m_Glass->UpdateInstancingData(objData.position, objData.rotation, objData.scale);
	}
	m_Glass->UpdateInstancingSTB();
}