#pragma once
#include "SourceFile/graphic/ModelRender.h"
#include "SourceFile/graphic/Decale.h"

class Weapon:public IGameObject
{
public:
	Weapon() {}
	~Weapon();
	bool Start();
	void Update();
	void Init(Skeleton* sk,bool DitherFlag = false);
	void AddDecale();
private:
	Skeleton* m_skeleton = nullptr;
	Vector3 m_weaponPos = Vector3::Zero;
	Quaternion m_weaponRot = Quaternion::Identity;
	Matrix m_weaponMat = Matrix::Identity;
	prefab::ModelRender* m_Model = nullptr;
	Decale* m_Decale = nullptr;
	int LeftHandBoneNo = -1;
};

