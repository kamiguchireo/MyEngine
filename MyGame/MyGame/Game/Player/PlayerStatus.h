#pragma once

class Player;
class PlayerStatus
{
public:
	PlayerStatus(Player* pn) :
		m_pl(pn)
	{

	}
	~PlayerStatus()
	{

	}

	//�_���[�W���󂯂�
	void Damage(int i);

	//�v���C���[�̎��S�t���O�𗧂Ă�
	void Dead();

private:
	Player* m_pl = nullptr;		//�G�l�~�[
	int m_hp = 100;		//�q�b�g�|�C���g
};

