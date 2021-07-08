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
	
	for (auto& objData : m_renderObjDatas)
	{
		auto boxCol = std::make_unique<PhysicsStaticObject>();
		Vector3 size = Vector3::One;
		size = { 65.0f,200.0f,65.0f };
		Vector3 colPos = objData.position;
		colPos.y += size.y / 2.0f;
		boxCol->CreateCylinder(colPos, objData.rotation, size);
		//���[�U�[�w��̃C���f�b�N�X���X�^�e�B�b�N�I�u�W�F�N�g�Ɏw��
		boxCol->GetRigidBody().GetBody()->setUserIndex(enCollisionAttr_StaticObject);
		m_Col.push_back(std::move(boxCol));
	}

	return true;
}

void Tree2::Update()
{
	m_Tree.Refresh();

	//�C���X�^���V���O�`��
	for (auto& objData : m_renderObjDatas)
	{
		m_Tree.UpdateInstancingData(objData.position, objData.rotation, objData.scale);
	}
	m_Tree.UpdateInstancingSTB();
}

void Tree2::Draw()
{
	auto& RenCon = g_graphicsEngine->GetRenderContext();
	m_Tree.Draw(RenCon);
}