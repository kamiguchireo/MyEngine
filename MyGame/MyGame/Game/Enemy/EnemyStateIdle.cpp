#include "stdafx.h"
#include "EnemyStateIdle.h"
#include "Enemy.h"

EnemyStateIdle::~EnemyStateIdle()
{

}

void EnemyStateIdle::Update()
{
	//�ҋ@�A�j���[�V�������Đ�
	m_Enemy->PlayAnimation(enEnemyAnimation_Rifle_Idle);
	//���݂̎��Ԃ����Z
	m_time += g_gameTime.GetFrameDeltaTime();
	//���݂̎��Ԃ��~�܂��Ă��鎞�Ԃ�蒷���Ȃ�����
	if (m_time >= stopTime)
	{
		//�X�g�b�v�t���O���Z�b�g����
		m_Enemy->SetIsStop(false);
		m_time = 0.0f;
	}
}