#include "stdafx.h"
#include "CameraStateTPS.h"

CameraStateTPS::CameraStateTPS()
{

}

CameraStateTPS::~CameraStateTPS()
{

}

void CameraStateTPS::Update(Vector3& /*pos*/, Vector3& target)
{
	//�E�X�e�B�b�N�̓��͗ʂ����]����ʂ����߂�
	rot -= g_pad[0]->GetRStickXF() * 0.05f;
	//�Œ���̍����̊m��
	target.y += 50.0f;
	//�ŏI�I�ȃJ�����̃|�W�V����
	Vector3 pos = target;
	//�ŏI�I�ȃJ�����̃^�[�Q�b�g�̃|�W�V����
	Vector3 targetPos = target;
	//�J�����̃^�[�Q�b�g�ɑ���Y�����̒l���E�X�e�B�b�N�̓��͗ʂ��猈�߂�
	AddTargetPosY += g_pad[0]->GetRStickYF()*2.0f;
	AddTargetPosY = min(max(-50.0f, AddTargetPosY), 200.0f);
	//�J�����̃^�[�Q�b�g�̃|�W�V�����ɑ���
	targetPos.y += AddTargetPosY;
	//�J�����̃|�W�V�����ɑ����x�N�g��
	Vector3 addPos = Vector3::Zero;
	//rot����J�����̈ʒu�����߂�
	addPos.x = sinf(rot) * CameraDist;
	addPos.y = 80.0f;
	addPos.z -= cosf(rot) * CameraDist;
	pos += addPos;

	//�J�����ɃZ�b�g
	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(targetPos);
}