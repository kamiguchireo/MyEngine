#pragma once

class Player;
//�v���C���[�̊��N���X
class IPlayer
{
public:
	IPlayer(Player* pl) :
		m_Player(pl) {}
	virtual ~IPlayer()
	{
	}
	//�X�V�֐�
	virtual void Update() = 0;

protected:
	Player* m_Player;
};

