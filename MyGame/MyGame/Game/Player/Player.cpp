#include "stdafx.h"
#include "Player.h"
#include "PlayerStateIdle.h"

Player::Player()
{
	//�ҋ@�X�e�[�g�ɐ؂�ւ���
	ChangeState<PlayerStateIdle>();
	//���f�������_�[�̃|�C���^�𐶐�
	m_playerModel = NewGO<prefab::ModelRender>(0, nullptr);
}

Player::~Player()
{
	if (currentState != nullptr)
	{
		delete currentState;
		currentState = nullptr;
	}
}

template<class T>void Player::ChangeState()
{
	if (currentState != nullptr)
	{
		delete currentState;
	}
	//���̏�Ԃ̃C���X�^���X���쐬����
	currentState = new T;
}

bool Player::Start()
{

	return true;
}

void Player::Update()
{

}

void Player::Draw()
{

}