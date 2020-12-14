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
	m_Model = NewGO<prefab::ModelRender>(0, nullptr);
	m_Model->SetTkmFilePath("Assets/modelData/monster.tkm");
	m_Model->SetVSEntryPoint("VSMain");

	Quaternion m_rot = Quaternion::Identity;
	m_rot.SetRotationDeg(Vector3::AxisX, 90.0f);
	Vector3 m_scale = Vector3::One;
	m_scale *= 3.0f;
	m_Model->SetScale(m_scale);
	m_Model->SetRotation(m_rot);
	m_Model->SetPosition(Vector3::Zero);
	return true;
}

void Test::Update()
{
	Quaternion qRot;
	if (g_pad[0]->IsPress(EnButton::enButtonRight)) {
		qRot.SetRotationDegY(1.0f);
	}
	else if (g_pad[0]->IsPress(EnButton::enButtonLeft)) {
		qRot.SetRotationDegY(-1.0f);
	}

	for (auto lig : g_graphicsEngine->GetLightManager()->GetLight().directionalLight) {
		qRot.Apply(lig.direction);
	}

	//ƒJƒƒ‰‚à‰ñ‚·B
	qRot.SetRotationDegY(g_pad[0]->GetLStickXF());
	auto camPos = g_camera3D->GetPosition();
	qRot.Apply(camPos);
	g_camera3D->SetPosition(camPos);

	Vector3 rotAxis;
	auto toPos = g_camera3D->GetPosition() - g_camera3D->GetTarget();
	auto dir = toPos;
	dir.Normalize();
	rotAxis.Cross(dir, g_vec3AxisY);
	qRot.SetRotationDeg(rotAxis, g_pad[0]->GetLStickYF());
	qRot.Apply(toPos);
	g_camera3D->SetPosition(g_camera3D->GetTarget() + toPos);
	
}