#include "stdafx.h"
#include "CameraStateAim.h"

CameraStateAim::CameraStateAim()
{

}

CameraStateAim::~CameraStateAim()
{

}

void CameraStateAim::Update(Vector3& /*pos*/, Vector3& target,float&rot)
{	
	//�}�E�X�J�[�\���̈ʒu���擾
	POINT pt;
	GetCursorPos(&pt);
	int lstx = pt.x;
	int lsty = pt.y;

	//�J�����̉�]�ʂ��}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	rot += (DefaultPoint[0] - lstx) * sensiX;
	//�Œ���̍����̊m��
	target.y += 90.0f;
	//�ŏI�I�ȃJ�����̃|�W�V����
	Vector3 pos = target;
	//�ŏI�I�ȃJ�����̃^�[�Q�b�g�̃|�W�V����
	Vector3 targetPos = target;
	//�J�����̃|�W�V�����ɑ���Y�����̒l���}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	*AddPosY -= (DefaultPoint[1] - lsty) * sensiY;

	*AddPosY = min(max(MinAddPos, *AddPosY), MaxAddPos);
	//�J�����̃|�W�V�����ɑ����x�N�g��
	Vector3 addPos = Vector3::Zero;
	//rot����J�����̈ʒu�����߂�
	addPos.x = sinf(rot) * CameraDist;
	addPos.y = *AddPosY;
	addPos.z -= cosf(rot) * CameraDist;
	pos += addPos;

	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	SetCursorPos(500, 300);

	//�J�����ɃZ�b�g
	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(targetPos);
}