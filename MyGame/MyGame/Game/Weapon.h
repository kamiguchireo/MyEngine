#pragma once
#include "SourceFile/graphic/ModelRender.h"

class Weapon:public IGameObject
{
public:
	Weapon() {}
	~Weapon();
	bool Start();
	void Update();

	//初期化
	//sk		スケルトン
	//IsDither		ディザリングを適応するかどうかのフラグ
	void Init(Skeleton* sk,bool IsDither = false);

	////デカールを追加
	//void AddDecale();
private:
	Skeleton* m_skeleton = nullptr;		//スケルトン
	//Vector3 m_weaponPos = Vector3::Zero;		//武器のポジション
	//Quaternion m_weaponRot = Quaternion::Identity;		//武器の回転
	Matrix m_weaponMat = Matrix::Identity;		//武器の行列
	prefab::ModelRender* m_Model = nullptr;		//モデル
	int LeftHandBoneNo = -1;		//武器用のボーン番号
};

