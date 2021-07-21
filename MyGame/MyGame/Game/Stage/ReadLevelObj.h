#pragma once
#include "Game/Enemy/Enemy.h"

class ReadLevelObj
{
public:
	ReadLevelObj() {}
	~ReadLevelObj() {}

	//���x���̃I�u�W�F�N�g�̃t�@�C���p�X�𓮓I�ɍ쐬���ēǂݍ��ޏꍇ�Ɏg�p���Ă�������
	Enemy* GetEnemyPtr(const wchar_t* ObjName,const Vector3& pos,const Quaternion& rot);

private:
	int Firstplace = 0;
	int Tenthplace = 0;
	bool m_IsEnemyInited[100] = { false };
	int m_numEnemy = 0;
};

