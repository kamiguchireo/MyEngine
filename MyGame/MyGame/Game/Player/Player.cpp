#include "stdafx.h"
#include "Player.h"

Player::Player()
{

}

Player::~Player()
{
	if (currentState != nullptr)
	{
		delete currentState;
		currentState = nullptr;
	}
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