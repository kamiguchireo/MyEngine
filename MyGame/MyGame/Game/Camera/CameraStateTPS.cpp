#include "stdafx.h"
#include "CameraStateTPS.h"

CameraStateTPS::CameraStateTPS()
{
	//�J�����R���W�����̏�����
	m_cameraCollisionSolver.Init(Col_Radius);
	//�}�E�X�J�[�\���̕\��������
	ShowCursor(false);
}

CameraStateTPS::~CameraStateTPS()
{

}

void CameraStateTPS::Update(Vector3& pivotpos,float& rot)
{
	//�}�E�X�J�[�\���̈ʒu���擾
	POINT pt;
	GetCursorPos(&pt);
	int lstx = pt.x;
	int lsty = pt.y;

	//�J�����̉�]�ʂ��}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	rot += (DefaultPoint[0] - lstx) * sensiX;
	//�ŏI�I�ȃJ�����̃|�W�V����
	Vector3 pos = pivotpos;
	//�ŏI�I�ȃJ�����̃^�[�Q�b�g�̃|�W�V����
	Vector3 targetPos = pivotpos;
	//�Œ���̍������m��
	{
		pos.y += 90.0f;
		targetPos.y += 90.0f;
	}
	//�J�����̃|�W�V�����ɑ���Y�����̒l���}�E�X�J�[�\���̈ʒu�Ə����l���r���ċ��߂�
	AddPosY -= (DefaultPoint[1] - lsty) * sensiY;

	AddPosY = min(max(MinAddPos, AddPosY), MaxAddPos);
	//�J�����̃|�W�V�����ɑ����x�N�g��
	Vector3 addPos = Vector3::Zero;
	//rot����J�����̈ʒu�����߂�
	addPos.x = sinf(rot) * CameraDist;
	addPos.y = AddPosY;
	addPos.z -= cosf(rot) * CameraDist;
	pos += addPos;

	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	SetCursorPos(500, 300);

	//�R���W����������̈ʒu
	Vector3 solve_pos = Vector3::Zero;
	m_cameraCollisionSolver.Execute(solve_pos, pos, targetPos);
	//�J�����ɃZ�b�g
	g_camera3D->SetPosition(solve_pos);
	g_camera3D->SetTarget(targetPos);
}