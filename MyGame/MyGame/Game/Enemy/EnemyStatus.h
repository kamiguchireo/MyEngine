#pragma once

class Enemy;
class EnemyStatus
{
public: 
	EnemyStatus(Enemy* en) :
		m_en(en)
	{

	}
	~EnemyStatus()
	{

	}

	//�_���[�W���󂯂�
	//i		�_���[�W��
	void Damage(int i);

	//�G�l�~�[�̎��S�t���O�𗧂Ă�
	void Dead();

private:
	int m_hp = 100;		//�q�b�g�|�C���g
	Enemy* m_en = nullptr;		//�G�l�~�[
};