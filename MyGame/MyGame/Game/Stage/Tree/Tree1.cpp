#include "stdafx.h"
#include "Tree1.h"

Tree1::Tree1()
{

}

Tree1::~Tree1()
{

}

bool Tree1::Start()
{
	m_InitData.m_tkmFilePath = "Assets/modelData/SM_Tree_Tropic_02_novines.tkm";
	m_InitData.m_vsEntryPointFunc = "VSMainInstancing";
	m_InitData.m_psEntryPointFunc = "PSMain";
	m_InitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	m_Tree.Init(m_InitData,m_instanceNum);
	m_Tree.SetShadowRecieverFlag(true);

	for (auto& objData : m_renderObjDatas)
	{
		auto boxCol = std::make_unique<PhysicsStaticObject>();
		Vector3 size = Vector3::One;
		size = { 40.0f,200.0f,40.0f };
		boxCol->CreateBox(objData.position, objData.rotation, size);
		m_boxCol.push_back(std::move(boxCol));
	}

	return true;
}

void Tree1::Update()
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

void Tree1::Draw()
{
	auto& RenCon = g_graphicsEngine->GetRenderContext();
	m_Tree.Draw(RenCon);
}