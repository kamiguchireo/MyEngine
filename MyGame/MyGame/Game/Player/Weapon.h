#pragma once
#include "SourceFile/graphic/ModelRender.h"

class Weapon:public IGameObject
{
public:
	Weapon() {}
	~Weapon();
	bool Start();
	void Update();
	void Init(Skeleton* sk);
private:
	Skeleton* m_skeleton = nullptr;
	Vector3 m_weaponPos = Vector3::Zero;
	Quaternion m_weaponRot = Quaternion::Identity;
	Matrix m_weaponMat = Matrix::Identity;
	prefab::ModelRender* m_Model = nullptr;
};

