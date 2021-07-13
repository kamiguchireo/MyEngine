#pragma once
#include "WaveFile.h"

class SoundSource :public IGameObject
{
public:
	SoundSource();
	~SoundSource();

	//������
	//�I���������Đ�����
	void Init(const wchar_t* filePath, bool is3DSound = false);

	//������
	//�X�g���[�~���O�Đ�����
	//ringBufferSize		�����O�o�b�t�@�̃T�C�Y
	//bufferSize		�X�g���[�~���O�̍ő�o�b�t�@�����O�̃T�C�Y
	void InitStreaming(wchar_t* filePath, bool is3DSound = false, unsigned int ringBufferSize = 3 * 1024 * 1024, unsigned int bufferSize = 1024 * 512);

	//�������
	void Release();

	//�Đ�
	//isLoop		���[�v�Đ��t���O
	//�����V���b�g�Đ��̏ꍇ�Đ�����������Ǝ����I�ɃC���X�^���X��j�����܂�
	//�����V���b�g�Đ���SoundSource�̃C���X�^���X�������o�ϐ��ŕێ����Ă����
	//�j�����ꂽ�C���X�^���X�ɃA�N�Z�X���Ă��܂��\��������܂�
	void Play(bool isLoop,bool IsDelete = true);

	//��~
	void Stop()
	{
		m_sourceVoice->Stop();
		m_isPlaying = false;
	}

	//�ꎞ��~
	void Pause()
	{
		m_sourceVoice->Stop();
	}

	//�Đ����H
	bool IsPlaying()const
	{
		return m_isPlaying;
	}

	//�{�����[����ݒ�
	void SetVolume(float vol)
	{
		m_sourceVoice->SetVolume(vol);
	}

	//�{�����[�����擾
	float GetVolume()const
	{
		float vol;
		m_sourceVoice->GetVolume(&vol);
		return vol;
	}

	//�����̍��W��ݒ�
	//3D�T�E���h�̎��ɕK�v�ɂȂ�܂�
	//2D�T�E���h�ł͖�������܂�
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
		if (m_isSetPositionFirst)
		{
			m_lastFramePosition = m_position;
			m_isSetPositionFirst = false;
		}
	}

	//�����̍��W���擾
	Vector3 GetPosition()const
	{
		return m_position;
	}

	//�����̈ړ����x���擾
	Vector3 GetVelocity()const
	{
		return m_velocity;
	}

	//�����̌���������ݒ�
	void SetCurveDistance(float dist)
	{
		m_CurveDistance = dist;
	}
	//�����̌����������擾
	float GetCurveDistance()
	{
		return m_CurveDistance;
	}
	//���[�v�t���O���擾
	bool GetLoopFlag()const
	{
		return m_isLoop;
	}

	//�{�C�X�̎��g������
	void SetFrequencyRatio(float ratio)
	{
		if (m_sourceVoice != nullptr)
		{
			m_sourceVoice->SetFrequencyRatio(ratio);
		}
	}

	IXAudio2SourceVoice* GetXAudio2SourceVoice()
	{
		return m_sourceVoice;
	}
	//���̓`�����l�������擾�B
	int GetNumInputChannel()const
	{
		return m_waveFile->GetFormat()->nChannels;
	}
	FLOAT32* GetEmitterAzimuths()
	{
		return m_emitterAzimuths;
	}
	FLOAT32* GetMatrixCoefficients()
	{
		return m_matrixCoefficients;
	}
	X3DAUDIO_DSP_SETTINGS* GetDspSettings()
	{
		return &m_dspSettings;
	}

private:
	void InitCommon();
	//�X�g���[�~���O�Đ����̍X�V�����B
	void UpdateStreaming();
	//�I���������Đ����̍X�V�����B
	void UpdateOnMemory();
	void Play(char* buff, unsigned int bufferSize);
	/*!
	* @brief	�X�g���[�~���O�o�b�t�@�����O�̊J�n�B
	*/
	void StartStreamingBuffring();
	void Remove3DSound();
	/*!
	* @brief	�X�V�B
	*/
	void Update() override;
private:
	enum EnStreamingStatus {
		enStreamingBuffering,	//�o�b�t�@�����O���B
		enStreamingQueueing,	//�L���[�C���O���B
	};
	std::shared_ptr<WaveFile>	m_waveFile;					//!<�g�`�f�[�^�B
	IXAudio2SourceVoice* m_sourceVoice = nullptr;	//!<�\�[�X�{�C�X�B
	bool						m_isLoop = false;			//!<���[�v�t���O�B
	bool						m_isPlaying = false;		//!<�Đ����t���O�B
	bool					m_isStreaming = false;		//!<�X�g���[�~���O�Đ��H
	unsigned int			m_streamingBufferSize = 0;	//!<�X�g���[�~���O�p�̃o�b�t�@�����O�T�C�Y�B
	unsigned int			m_currentBufferingSize = 0;	//!<���݂̃o�b�t�@�����O�̃T�C�Y�B
	unsigned int			m_readStartPos = 0;			//!<�ǂݍ��݊J�n�ʒu�B
	unsigned int			m_ringBufferSize = 0;		//!<�����O�o�b�t�@�̃T�C�Y�B
	EnStreamingStatus		m_streamingState = enStreamingBuffering;	//!<�X�g���[�~���O�X�e�[�^�X�B
	bool					m_is3DSound = false;		//!<3D�T�E���h�H
	Vector3				m_position = Vector3::Zero;	//!<�����̍��W�B3D�T�E���h�̎��ɕK�v�B
	Vector3				m_lastFramePosition = Vector3::Zero;//!<������1�t���[���O�̍��W�B3D�T�E���h�̎��ɕK�v�B
	Vector3				m_velocity = Vector3::Zero;	//!<���x�B3D�T�E���h�̎��ɕK�v�E
	FLOAT32 m_emitterAzimuths[INPUTCHANNELS];
	FLOAT32 m_matrixCoefficients[INPUTCHANNELS * OUTPUTCHANNELS];
	X3DAUDIO_DSP_SETTINGS m_dspSettings;
	bool m_isSetPositionFirst = true;	//!<��ԍŏ���setPosition?
	bool m_isAvailable = false;			//!<�C���X�^���X�����p�\�H
	bool m_IsDeleteOnOneShot = true;
	float m_CurveDistance = 1000.0f;
};