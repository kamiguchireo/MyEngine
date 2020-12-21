#include "stdafx.h"
#include "PlayerStateMove.h"
#include "Player.h"

PlayerStateMove::~PlayerStateMove()
{

}

void PlayerStateMove::Update()
{
	m_Player->PlayAnimation(1);
	//��]
	Quaternion q_rot = Quaternion::Identity;
	//�v���C���[�̑O����
	Vector3 playerforward = Vector3::Zero;
	//�ړ�����
	Vector3 movedir = Vector3::Zero;
	
	//�v���C���[�̑O�������Q�b�g
	playerforward = m_Player->GetForward();
	//�J�����̑O�������Q�b�g
	movedir = g_camera3D->GetForward();
	movedir.y = 0.0f;
	movedir.Normalize();

	//�L�[���͂ɂ��ړ������̌v�Z
	//�܂��̓J�����̈ړ��������v�Z
	Vector3 KeyDir = playerforward * g_pad[0]->GetLStickYF();
	//�J�����̉E�������Q�b�g
	Vector3 playerRight = Cross(playerforward, { 0.0f,1.0f,0.0f });
	//�J�����̍��E�̈ړ��������v�Z
	KeyDir += playerRight* g_pad[0]->GetLStickXF();
	KeyDir.Normalize();

	//��]���v�Z
	q_rot.SetRotation(KeyDir, movedir);

	//�v���C���[�ɉ�]���Z�b�g
	m_Player->SetRotation(q_rot);
}
