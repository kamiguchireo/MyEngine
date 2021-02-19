#include "stdafx.h"
#include "CameraStateTPS.h"

CameraStateTPS::CameraStateTPS()
{
	ShowCursor(false);
}

CameraStateTPS::~CameraStateTPS()
{

}

void CameraStateTPS::Update(Vector3& /*pos*/, Vector3& target)
{
	POINT pt;
	GetCursorPos(&pt);
	int lstx = pt.x;
	int lsty = pt.y;

	//�E�X�e�B�b�N�̓��͗ʂ����]����ʂ����߂�
	//rot -= g_pad[0]->GetRStickXF() * 0.05f;
	rot += (DefaultPoint[0] - lstx) * sensiX;
	//�Œ���̍����̊m��
	target.y += 90.0f;
	//�ŏI�I�ȃJ�����̃|�W�V����
	Vector3 pos = target;
	//�ŏI�I�ȃJ�����̃^�[�Q�b�g�̃|�W�V����
	Vector3 targetPos = target;
	//�J�����̃|�W�V�����ɑ���Y�����̒l���E�X�e�B�b�N�̓��͗ʂ��猈�߂�
	//AddPosY -= g_pad[0]->GetRStickYF()*2.0f;
	AddPosY -= (DefaultPoint[1] - lsty) * sensiY;

	AddPosY = min(max(MinAddPos, AddPosY), MaxAddPos);
	//�J�����̃|�W�V�����ɑ����x�N�g��
	Vector3 addPos = Vector3::Zero;
	//rot����J�����̈ʒu�����߂�
	addPos.x = sinf(rot) * CameraDist;
	addPos.y = AddPosY;
	addPos.z -= cosf(rot) * CameraDist;
	pos += addPos;

	SetCursorPos(500, 300);
	//�J�����ɃZ�b�g
	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(targetPos);
}