#pragma once

class Enemy;
class IEnemy
{
public:
	IEnemy(Enemy* en) :
		m_Enemy(en) {}
	
	virtual ~IEnemy()
	{
	}

	//XVŠÖ”
	virtual void Update() = 0;

protected:
	Enemy* m_Enemy;
};

