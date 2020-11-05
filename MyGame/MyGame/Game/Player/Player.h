#pragma once
#include "IPlayer.h"
#include "SourceFile/graphic/ModelRender.h"

class Player:public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Draw();

private:
	template<class T> void ChangeState();
private:
	IPlayer* currentState = nullptr;		//���݂̃X�e�[�g
	prefab::ModelRender* m_playerModel = nullptr;		//�v���C���[�̃��f��
};
