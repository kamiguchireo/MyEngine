#pragma once
#include "Game/Enemy/Enemy.h"
#include "Path.h"
//���x���̃I�u�W�F�N�g�̃t�@�C���p�X�𓮓I�ɍ쐬���ēǂݍ��ޏꍇ�Ɏg�p���Ă�������

class ReadLevelObj
{
public:
	ReadLevelObj() {}
	~ReadLevelObj() {}

	//�G�l�~�[�̃I�u�W�F�N�g������΃|�C���^���쐬���ĕԂ��܂�
	Enemy* GetEnemyPtr(const wchar_t* ObjName,const Vector3& pos,const Quaternion& rot);
	
	//�G�l�~�[�̎g�p����p�X������΃|�C���^���쐬���ĕԂ��܂�
	bool GetPathPtr(const wchar_t* objName, const Vector3& pos, std::vector<Path*>& m_Path);

private:
	int Firstplace = 0;
	int Tenthplace = 0;
	bool m_IsEnemyInited[100] = { false };
	bool m_IsPathInited[100] = { false };
	int m_numEnemy = 0;
	int m_numPath = 0;
};

