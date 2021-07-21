#pragma once
#include "Game/Enemy/Enemy.h"
#include "Path.h"
//レベルのオブジェクトのファイルパスを動的に作成して読み込む場合に使用してください

class ReadLevelObj
{
public:
	ReadLevelObj() {}
	~ReadLevelObj() {}

	//エネミーのオブジェクトがあればポインタを作成して返します
	Enemy* GetEnemyPtr(const wchar_t* ObjName,const Vector3& pos,const Quaternion& rot);
	
	//エネミーの使用するパスがあればポインタを作成して返します
	bool GetPathPtr(const wchar_t* objName, const Vector3& pos, std::vector<Path*>& m_Path);

private:
	int Firstplace = 0;
	int Tenthplace = 0;
	bool m_IsEnemyInited[100] = { false };
	bool m_IsPathInited[100] = { false };
	int m_numEnemy = 0;
	int m_numPath = 0;
};

