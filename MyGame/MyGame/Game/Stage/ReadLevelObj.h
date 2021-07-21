#pragma once
#include "Game/Enemy/Enemy.h"

class ReadLevelObj
{
public:
	ReadLevelObj() {}
	~ReadLevelObj() {}

	//レベルのオブジェクトのファイルパスを動的に作成して読み込む場合に使用してください
	Enemy* GetEnemyPtr(const wchar_t* ObjName,const Vector3& pos,const Quaternion& rot);

private:
	int Firstplace = 0;
	int Tenthplace = 0;
	bool m_IsEnemyInited[100] = { false };
	int m_numEnemy = 0;
};

