#include "stdafx.h"
#include "PlayerStateMove.h"
#include "Player.h"

PlayerStateMove::~PlayerStateMove()
{

}

void PlayerStateMove::Update()
{
	if (GetAsyncKeyState(VK_LSHIFT))
	{	
		//��SHIFT��������Ă���Ƃ�
		//�X�v�����g�A�j���[�V�������Đ�
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Sprint);
	}
	else if (GetAsyncKeyState(VK_LCONTROL))
	{
		//��CONTROL��������Ă���Ƃ�
		//�����A�j���[�V�������Đ�
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Walk);
	}
	else
	{
		//����ȊO�ł�
		//����A�j���[�V�������Đ�
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Run);
	}
	//�ړ�����
	Vector3 movedir = Vector3::Zero;
	
	//�J�����̑O�������Q�b�g
	movedir = g_camera3D->GetForward();
	movedir.y = 0.0f;
	movedir.Normalize();

	//�L�[���͂ɂ��ړ������̌v�Z
	//�܂��̓J�����̈ړ��������v�Z
	Vector3 KeyDir = movedir * g_pad[0]->GetLStickYF();
	//�J�����̉E�������Q�b�g
	Vector3 playerRight = Cross(Vector3::Up, movedir);
	//�J�����̍��E�̈ړ��������v�Z
	KeyDir += playerRight* g_pad[0]->GetLStickXF();
	KeyDir.Normalize();

	//�v���C���[�̑O�������Z�b�g
	m_Player->SetForward(KeyDir);
	//�v���C���[�̉E�������Z�b�g
	m_Player->SetRight(playerRight);
}
