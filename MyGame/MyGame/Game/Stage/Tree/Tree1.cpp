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
	m_Tree = NewGO<prefab::ModelRender>(1);
	m_Tree->SetTkmFilePath("Assets/modelData/SM_Tree_Tropic_02_novines.tkm");
	m_Tree->SetVSEntryPoint("VSMainInstancing");
	m_Tree->SetPSEntryPoint("PSMain");
	m_Tree->SetfxFilePath("Assets/shader/NoAnimModel_LambertSpecularAmbient.fx");
	m_Tree->SetInstanceNum(m_instanceNum);
	m_Tree->SetShadowRecieverFlag(true);
	m_Tree->SetShadowCasterFlag(false);
	m_Tree->SetIsDefferd(false);
	//m_InitData.m_tkmFilePath = "Assets/modelData/SM_Tree_Tropic_02_novines.tkm";
	//m_InitData.m_vsEntryPointFunc = "VSMainInstancing";
	//m_InitData.m_psEntryPointFunc = "PSMain";
	//m_InitData.m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";
	//m_Tree.Init(m_InitData,m_instanceNum);
	//m_Tree.SetShadowRecieverFlag(true);

	for (auto& objData : m_renderObjDatas)
	{
		auto boxCol = std::make_unique<PhysicsStaticObject>();
		Vector3 size = Vector3::One;
		size = { 60.0f,200.0f,60.0f };
		Vector3 colPos = objData.position;
		colPos.y += size.y / 2.0f;
		boxCol->CreateCylinder(colPos, objData.rotation, size);
		m_Col.push_back(std::move(boxCol));
	}

	return true;
}

void Tree1::Update()
{
	//m_Tree.Refresh();
	m_Tree->ModelInstanceRefresh();
	//インスタンシング描画
	for (auto& objData : m_renderObjDatas) 
	{
		//m_Tree.UpdateInstancingData(objData.position, objData.rotation, objData.scale);
		m_Tree->UpdateInstancingData(objData.position, objData.rotation, objData.scale);
	}
	//m_Tree.UpdateInstancingSTB();
	m_Tree->UpdateInstancingSTB();
	//g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_Tree);
}

void Tree1::Draw()
{
	//auto& RenCon = g_graphicsEngine->GetRenderContext();
	//m_Tree.Draw(RenCon);
}