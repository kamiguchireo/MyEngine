#include "stdafx.h"
#include "Test.h"

Test::Test()
{

}

Test::~Test()
{
	if (m_Model != nullptr)
	{
		DeleteGO(m_Model);
	}
}

bool Test::Start()
{
	g_camera3D->SetPosition({ 0.0f,300.0f,1000.0f });
	g_camera3D->SetTarget({ 0.0f,300.0f,0.0f });

	for (int i = 0; i < 2; i++)
	{
		//–Ø
		if (m_Tree == nullptr)
		{
			m_Tree = NewGO<Tree2>(0);
			m_Tree->InitInstance(Vector3::Zero, Quaternion::Identity, Vector3::One);
		}
		else
		{
			m_Tree->AddInstance(Vector3::Zero, Quaternion::Identity, Vector3::One);
		}
	}
	return true;
}

void Test::Update()
{
	
}