#include "stdafx.h"
#include "PlayerStateAim.h"
#include "Player.h"

PlayerStateAim::~PlayerStateAim()
{

}

void PlayerStateAim::WaistBend()
{
	//�J�����̑O�������擾
	Vector3 aimForward = g_camera3D->GetForward();
	//��ɐ��K�����邱�Ƃ�y������1�̎��^��������Ă���悤�ɂȂ�
	aimForward.Normalize();
	//�p�x�����߂�
	float RotY = aimForward.y * -45.0f;
	//X������̉�]�s��
	Quaternion qRot = Quaternion::Identity;
	qRot.SetRotationDegX(RotY);
	//qRot.SetRotationDegX(atan2f(aimForward.z, aimForward.y));
	Matrix mRot = Matrix::Identity;
	mRot.MakeRotationFromQuaternion(qRot);
	//mRot.MakeRotationAxis(Vector3::AxisX, RotY);
	//�v���C���[�̍�����]
	m_plSkeleton->GetBone(m_SpineBoneNum)->SetUserMat(mRot);
	//m_plSkeleton->GetBone(m_RightArmBoneNum)->SetUserMat(mRot);
}

void PlayerStateAim::UpdateRotation()
{
	//�J�����̑O�������擾
	Vector3 aimForward = g_camera3D->GetForward();
	//y�����͕K�v�Ȃ��̂�0�ɂ���
	aimForward.y = 0.0f;
	//���K��
	aimForward.Normalize();
	//��̃x�N�g���ɒ��s����x�N�g�����擾
	Vector3 Axis = Cross(Vector3::Front, aimForward);
	//���K��
	Axis.Normalize();
	//�x�N�g���̑傫��1�Ȃ̂œ�̃x�N�g����cos�Ƃ݂̂��c��
	float dot = Dot(Vector3::Front, aimForward);
	Quaternion rot = Quaternion::Identity;
	//�v���C���[�����_�����ɉ�]
	rot.SetRotation(Axis, acosf(dot));
	//�v���C���[�ɓK��
	m_Player->SetRotation(rot);
	//����������]
	WaistBend();
}

void PlayerStateAim::Init()
{
	m_plSkeleton = m_Player->GetSkeleton();
	m_SpineBoneNum = m_plSkeleton->FindBoneID(L"mixamorig:Spine");
}



void PlayerStateAim::Update()
{	
	//��]�̍X�V
	UpdateRotation();

	//�}�E�X�̍��{�^���������ꂽ"
	if (GetKeyState(VK_LBUTTON) & (0x80))
	{
		//�A�j���[�V�������Đ�
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_fire);
		m_Player->Shooting();
	}
	else
	{
		//�A�j���[�V�������Đ�
		m_Player->PlayAnimation(enPlayerAnimation_Rifle_Down_To_Aim);
		//m_Player->StopFiresound();
	}
}