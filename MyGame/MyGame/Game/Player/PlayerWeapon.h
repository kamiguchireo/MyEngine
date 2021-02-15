#pragma once
#include "IPlayer.h"

class PlayerWeapon:public IPlayer
{
public:
	PlayerWeapon(Player* pl) :IPlayer(pl) {}
	~PlayerWeapon();
	void Start();
	void Update();
	void Init();
private:
	Vector3 m_weaponPos = Vector3::Zero;
	Quaternion m_weaponRot = Quaternion::Identity;
	Matrix m_weaponMat = Matrix::Identity;
	prefab::ModelRender* m_Model = nullptr;
};

