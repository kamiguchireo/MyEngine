#include "stdafx.h"
#include "Bush_02.h"

Bush_02::Bush_02()
{

}

Bush_02::~Bush_02()
{

}

void Bush_02::OnDestroy()
{
	if (m_Bush != nullptr)
	{
		DeleteGO(m_Bush);
		m_Bush = nullptr;
	}
}
bool Bush_02::Start()
{
	m_Bush = NewGO<prefab::ModelRender>(1);
	m_Bush->SetTkmFilePath("Assets/modelData/SM_BushA_02.tkm");
	m_Bush->SetVSEntryPoint("VSMainInstancing");
	m_Bush->SetPSEntryPoint("PSMain");
	m_Bush->SetfxFilePath("Assets/shader/NoAnimModel_LambertSpecularAmbient.fx");
	m_Bush->SetInstanceNum(m_instanceNum);
	m_Bush->SetShadowRecieverFlag(true);
	m_Bush->SetShadowCasterFlag(false);
	m_Bush->SetIsDefferd(false);
	
	return true;
}

void Bush_02::Update()
{
	m_Bush->ModelInstanceRefresh();

	//インスタンシング描画
	for (auto& objData : m_renderObjDatas) 
	{
		m_Bush->UpdateInstancingData(objData.position, objData.rotation, objData.scale);
	}
	m_Bush->UpdateInstancingSTB();
}