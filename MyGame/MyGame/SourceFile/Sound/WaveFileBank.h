#pragma once
#include <map>
#include "SourceFile/NameKey.h"
#include "SourceFile/Noncopyable.h"

class WaveFile;
typedef std::shared_ptr<WaveFile> WaveFilePtr;
typedef std::map<unsigned int, WaveFilePtr> WaveFilePtrMap;

//�g�`�f�[�^�o���O
//��x���[�h���ꂽ�g�`�f�[�^���o���N�ɓo�^���邱�Ƃ�
//�o�^���ꂽ�g�`�f�[�^�͍ēx�ǂݍ��݂��s���K�v���Ȃ��Ȃ�
class WaveFileBank : Engine::Noncopyable
{
public:
	WaveFileBank();
	~WaveFileBank();

	//�g�`�f�[�^��o�^
	//groupID		�O���[�vID
	//waveFile		�g�`�f�[�^
	void RegistWaveFile(int groupID, WaveFilePtr waveFile);

	//�����Ŏw�肵���t�@�C���p�X�̔g�`�f�[�^���o���N�ɓo�^����Ă��邩��������
	//groupID		�O���[�vID
	//filePath		�t�@�C���p�X
	WaveFilePtr FindWaveFile(int groupID, const wchar_t* filePath);

	//�����Ŏw�肵���t�@�C���p�X�̔g�`�f�[�^���o���N�ɓo�^����Ă��邩��������
	//�l�[���L�[���g�p����
	WaveFilePtr FindWaveFile(int groupID, const WNameKey& nameKey);

	//�g�`�f�[�^���o���N����o�^����
	//groupID		�O���[�vID
	//waveFile		�g�`�f�[�^
	void UnregistWaveFile(int groupID, WaveFilePtr waveFile);

	//�O���[�v�P�ʂŉ��
	void Release(int groupID);

	//�S�ĉ��
	void ReleaseAll()
	{
		for (int i = 0; i < MAX_GROUP; i++)
		{
			Release(i);
		}
	}

private:
	static const int MAX_GROUP = 256;
	WaveFilePtrMap	m_waveFileMap[MAX_GROUP];		//!<wave�t�@�C���̃��X�g�B
};