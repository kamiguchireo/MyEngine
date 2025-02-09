#include "stdafx.h"
#include "Tree2.h"

Tree2::Tree2()
{

}

Tree2::~Tree2()
{

}

void Tree2::OnDestroy()
{
	if (m_Tree != nullptr)
	{
		DeleteGO(m_Tree);
		m_Tree = nullptr;
	}
}

bool Tree2::Start()
{
	m_Tree = NewGO<prefab::ModelRender>(1);
	m_Tree->SetTkmFilePath("Assets/modelData/SM_Tree_Tropic_02.tkm");
	m_Tree->SetVSEntryPoint("VSMainInstancing");
	m_Tree->SetPSEntryPoint("PSMain");
	m_Tree->SetfxFilePath("Assets/shader/NoAnimModel_LambertSpecularAmbient.fx");
	m_Tree->SetInstanceNum(m_instanceNum);
	m_Tree->SetShadowRecieverFlag(true);
	m_Tree->SetShadowCasterFlag(false);
	m_Tree->SetIsDefferd(false);
	
	for (auto& objData : m_renderObjDatas)
	{
		auto boxCol = std::make_unique<PhysicsStaticObject>();
		Vector3 size = Vector3::One;
		size = { 65.0f,200.0f,65.0f };
		Vector3 colPos = objData.position;
		colPos.y += size.y / 2.0f;
		boxCol->CreateCylinder(colPos, objData.rotation, size);
		//ユーザー指定のインデックスをスタティックオブジェクトに指定
		boxCol->GetRigidBody().GetBody()->setUserIndex(enCollisionAttr_StaticObject);
		m_Col.push_back(std::move(boxCol));
	}

	return true;
}

void Tree2::Update()
{
	m_Tree->ModelInstanceRefresh();

	//インスタンシング描画
	for (auto& objData : m_renderObjDatas)
	{
		m_Tree->UpdateInstancingData(objData.position, objData.rotation, objData.scale);
	}
	m_Tree->UpdateInstancingSTB();
}