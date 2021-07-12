#pragma once
#include <thread>

class WaveFile
{
public:
	WaveFile();
	~WaveFile();

	//�������
	void Release();

	//wave�t�@�C�����I�[�v��
	bool Open(const wchar_t* fileName);

	//�g�`�f�[�^��ǂݍ���
	//pBuffer		�g�`�f�[�^���������ރo�b�t�@
	//sizeToRead		�ǂݍ��ރf�[�^�T�C�Y
	void Read(char* pBuffer, unsigned int sizeToRead, unsigned int* currentReadSize);

	//�g�`�f�[�^��񓯊��ǂݍ���
	//pBuffer		�g�`�f�[�^���������ރo�b�t�@
	//sizeToRead		�ǂݍ��ރf�[�^�T�C�Y
	void ReadAsync(char* pBuffer, unsigned int sizeToRead, unsigned int* currentReadSize);

	//�ǂݍ��ݏI������
	bool IsReadEnd()const
	{
		return m_isReadEnd;
	}

	//�g�`�f�[�^�̃V�[�N�ʒu�����Z�b�g
	void ResetFile();

	//�t�@�C���T�C�Y���擾
	DWORD GetSize()const
	{
		return m_dwSize;
	}

	//�t�@�C���t�H�[�}�b�g���擾
	WAVEFORMATEX* GetFormat()const
	{
		return m_pwfx;
	}

	//�t�@�C���p�X�̃n�b�V���l���擾
	unsigned int GetFilePathHash()const
	{
		return m_filePathHash;
	}
	
	//�ǂݍ��ݐ�̃o�b�t�@���m��
	void AllocReadBuffer(int size)
	{
		m_readBuffer.reset(new char[size]);
	}

	//�ǂݍ��ݐ�̃o�b�t�@���擾
	char* GetReadBuffer()
	{
		return m_readBuffer.get();
	}
private:
	std::unique_ptr<char[]>	m_readBuffer = nullptr;	//�ǂݍ��ݐ�̃o�b�t�@�B
	HMMIO			m_hmmio = nullptr;	//Wave�t�@�C���n���h���B
	WAVEFORMATEX* m_pwfx = nullptr;  //wave�t�@�C���̃t�H�[�}�b�g��`�B
	MMCKINFO 		m_ckRiff;      // Use in opening a WAVE file
	DWORD			m_dwSize = 0;      // The size of the wave file
	MMCKINFO		m_ck;          // Multimedia RIFF chunk
	BYTE* m_pbData = nullptr;
	BYTE* m_pbDataCur = nullptr;
	ULONG			m_ulDataSize = 0;
	volatile bool	m_isReadEnd = true;	//�ǂݍ��ݏI���t���O�B
	std::thread		m_readAsyncThread;	//�񓯊��ǂݍ��݃X���b�h�B
	bool			m_isInvokeReadAsyncThread = false;
	std::wstring	m_filePath;			//�t�@�C���p�X�B
	unsigned int	m_filePathHash = 0;		//�t�@�C���p�X�̃n�b�V���R�[�h�B
};  