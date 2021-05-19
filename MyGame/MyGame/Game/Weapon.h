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

	//射撃
	void shooting();

private:
	//デカールを追加
	//start		始点
	//end		終点
	void AddDecale(const btVector3& start, const btVector3& end);

private:
	Skeleton* m_skeleton = nullptr;		//スケルトン
	Vector3 m_weaponPos = Vector3::Zero;		//武器のポジション
	Quaternion m_weaponRot = Quaternion::Identity;		//武器の回転
	Matrix m_weaponMat = Matrix::Identity;		//武器の行列
	prefab::ModelRender* m_Model = nullptr;		//モデル
	int LeftHandBoneNo = -1;		//武器用のボーン番号
	const float m_range = 1000.0f;		//射程
};

