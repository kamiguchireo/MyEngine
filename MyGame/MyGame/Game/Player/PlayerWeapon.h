#pragma once
#include "SourceFile/graphic/ModelRender.h"

class Player;
class PlayerWeapon:public IGameObject
{
public:
	PlayerWeapon() {}
	~PlayerWeapon();
	bool Start();
	void Update();
	void Init(Player*pl);
private:
	Player* m_Player = nullptr;
	Vector3 m_weaponPos = Vector3::Zero;
	Quaternion m_weaponRot = Quaternion::Identity;
	Matrix m_weaponMat = Matrix::Identity;
	prefab::ModelRender* m_Model = nullptr;
};

