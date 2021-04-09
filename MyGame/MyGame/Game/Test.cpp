#include "stdafx.h"
#include "Test.h"

Test::Test()
{
	m_enemy = NewGO<Enemy>(0, nullptr);
}

Test::~Test()
{

}

bool Test::Start()
{
	g_camera3D->SetPosition({ 0.0f,300.0f,1000.0f });
	g_camera3D->SetTarget({ 0.0f,300.0f,0.0f });

	Vector3 size = Vector3::One;
	size *= 100.0f;
	m_GhostObject.CreateBox(m_pos, Quaternion::Identity, size);
	
	return true;
}

void Test::Update()
{
	m_pos.x += g_pad[0]->GetLStickXF();
	m_pos.z += g_pad[0]->GetLStickYF();
	m_GhostObject.UpdateWorldMatrix(m_pos, Quaternion::Identity);
}