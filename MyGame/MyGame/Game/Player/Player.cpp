#include "stdafx.h"
#include "Player.h"
#include "PlayerStateIdle.h"

Player::Player()
{
	//待機ステートに切り替える
	ChangeState<PlayerStateIdle>();
	//モデルレンダーのポインタを生成
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
	//次の状態のインスタンスを作成する
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