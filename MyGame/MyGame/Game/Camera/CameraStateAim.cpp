#include "stdafx.h"
#include "CameraStateAim.h"

CameraStateAim::CameraStateAim()
{
}

CameraStateAim::~CameraStateAim()
{

}

void CameraStateAim::Update(Vector3& pivotpos,float&rot)
{	
	//�}�E�X�J�[�\���̈ʒu���擾
	POINT pt;
	GetCursorPos(&pt);
	int lstx = pt.x;
	int lsty = pt.y;

	//�J�����̉�]�ʂ��}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	rot += (DefaultPoint[0] - lstx) * sensiX;
	//�ŏI�I�ȃJ�����̃|�W�V����
	Vector3 m_pos = pivotpos;
	//�ŏI�I�ȃJ�����̃^�[�Q�b�g�̃|�W�V����
	Vector3 targetPos = pivotpos;
	//�Œ���̍����̊m��
	targetPos.y = DefaultCameraHeight;
	
	//�J�����̃|�W�V�����ɑ���Y�����̒l���}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	AddPosY += (DefaultPoint[1] - lsty) * sensiY;

	AddPosY = min(max(MinAddPos, AddPosY), MaxAddPos);
	//�J�����̃|�W�V�����ɑ����x�N�g��
	Vector3 addPos = Vector3::Zero;
	//rot����J�����̃^�[�Q�b�g�̈ʒu�����߂�
	addPos.x -= sinf(rot) * CameraDist;
	addPos.y += AddPosY;
	addPos.z = cosf(rot) * CameraDist;
	targetPos += addPos;
	
	m_pos.y += DefaultCameraHeight;
	Vector3 AddPos = g_camera3D->GetForward();
	m_pos = m_HeadPos;
	AddPos.y = 0.0f;
	AddPos.Normalize();
	m_pos += AddPos * 15.0f;
	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	SetCursorPos(DefaultPoint[0], DefaultPoint[1]);

	//�J�����ɃZ�b�g
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(targetPos);
}