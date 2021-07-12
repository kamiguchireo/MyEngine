#include "stdafx.h"
#include "SoundSource.h"


SoundSource::SoundSource()
{
	memset(m_emitterAzimuths, 0, sizeof(m_emitterAzimuths));
	memset(m_matrixCoefficients, 0, sizeof(m_matrixCoefficients));
}
SoundSource::~SoundSource()
{
	Release();
}
void SoundSource::InitCommon()
{
	m_dspSettings.SrcChannelCount = INPUTCHANNELS;
	m_dspSettings.DstChannelCount = g_engine->GetSoundEngine().GetNumChannel();
	m_dspSettings.pMatrixCoefficients = m_matrixCoefficients;
	m_dspSettings.pDelayTimes = nullptr;
	m_dspSettings.DopplerFactor = 1.0f;
	m_dspSettings.LPFDirectCoefficient = 0.82142854f;
	m_dspSettings.LPFReverbCoefficient = 0.75f;
	m_dspSettings.ReverbLevel = 0.69114286f;
	m_dspSettings.EmitterToListenerAngle = 0.0f;
	m_dspSettings.EmitterToListenerDistance = 10.0f;
	m_dspSettings.EmitterVelocityComponent = 0.0f;
	m_dspSettings.ListenerVelocityComponent = 0.0f;
}
void SoundSource::Init(const wchar_t* filePath, bool is3DSound)
{
	if (g_engine->GetSoundEngine().IsAvailable() == false) {
		//�T�E���h�G���W�������p�s�B
		return;
	}	
	m_waveFile = g_engine->GetSoundEngine().GetWaveFileBank().FindWaveFile(0, filePath);
	if (!m_waveFile) {
		m_waveFile.reset(new WaveFile);
		bool result = m_waveFile->Open(filePath);
		if (result == false) {
			//wave�t�@�C���̓ǂݍ��݂Ɏ��s�B
			g_engine->GetSoundEngine().GetWaveFileBank().UnregistWaveFile(0, m_waveFile);
			m_waveFile.reset();
			return;
		}

		m_waveFile->AllocReadBuffer(m_waveFile->GetSize());	//wave�t�@�C���̃T�C�Y���̓ǂݍ��݃o�b�t�@���m�ۂ���B
		g_engine->GetSoundEngine().GetWaveFileBank().RegistWaveFile(0, m_waveFile);
		unsigned int dummy;
		m_waveFile->Read(m_waveFile->GetReadBuffer(), m_waveFile->GetSize(), &dummy);
		m_waveFile->ResetFile();

	}
	//�T�E���h�{�C�X�\�[�X���쐬�B
	m_sourceVoice = g_engine->GetSoundEngine().CreateXAudio2SourceVoice(m_waveFile.get(), is3DSound);
	if (is3DSound) {
		//�T�E���h�G���W����3D�����Ƃ��Ēǉ�
		g_engine->GetSoundEngine().Add3DSoundSource(this);
	}
	InitCommon();

	m_is3DSound = is3DSound;
	m_isAvailable = true;
}

void SoundSource::InitStreaming(wchar_t* filePath, bool is3DSound, unsigned int ringBufferSize, unsigned int bufferSize)
{
	if (g_engine->GetSoundEngine().IsAvailable() == false)
	{
		//�T�E���h�G���W�������p�s��
		return;
	}
	m_isAvailable = false;
	//�X�g���[�~���O��WaveFile�̎g���܂킵�͂ł��Ȃ�
	m_waveFile.reset(new WaveFile);
	m_waveFile->Open(filePath);

	m_isStreaming = true;
	m_streamingBufferSize = bufferSize;
	m_waveFile->AllocReadBuffer(ringBufferSize);
	m_ringBufferSize = ringBufferSize;
	m_readStartPos = 0;
	m_currentBufferingSize = 0;
	//�T�E���h�{�C�X�\�[�X���쐬
	m_sourceVoice = g_engine->GetSoundEngine().CreateXAudio2SourceVoice(m_waveFile.get(), is3DSound);
	if (is3DSound)
	{
		//�T�E���h�G���W����3D�����Ƃ��Ēǉ�
		g_engine->GetSoundEngine().Add3DSoundSource(this);
	}
	InitCommon();
	m_is3DSound = is3DSound;
	m_isAvailable = true;
}
void SoundSource::Release()
{
	if (m_isStreaming) {
		if (m_waveFile) {
			m_waveFile->Release();
		}
	}
	if (m_sourceVoice != nullptr) {
		m_sourceVoice->DestroyVoice();
		m_sourceVoice = nullptr;
	}
	Remove3DSound();
	DeleteGO(this);
}

void SoundSource::Play(char* buff, unsigned int bufferSize)
{
	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = (BYTE*)buff;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = bufferSize;
	if (m_sourceVoice != nullptr && bufferSize > 0)
	{
		//�Đ��J�n
		if (FAILED(m_sourceVoice->SubmitSourceBuffer(&buffer)))
		{
			Release();
			//Failed m_sourceVoice->SubmitSourceBuffer
			std::abort();
		}
	}
}

void SoundSource::StartStreamingBuffring()
{
	char* readStartBuff = m_waveFile->GetReadBuffer();
	m_readStartPos += m_currentBufferingSize;
	if (m_readStartPos += m_streamingBufferSize >= m_ringBufferSize)
	{
		//�����O�o�b�t�@�̃T�C�Y�𒴂���̂�0�ɖ߂�
		m_readStartPos = 0;
	}
	m_waveFile->ReadAsync(&readStartBuff[m_readStartPos], m_streamingBufferSize, &m_currentBufferingSize);
	m_streamingState = EnStreamingStatus::enStreamingBuffering;
}

void SoundSource::Play(bool isLoop,bool IsDelete)
{
	if (m_isAvailable == false)
	{
		return;
	}
	if (m_isPlaying)
	{
		//�Đ����̂��̂��ĊJ����
		m_sourceVoice->Start(0);
	}
	else
	{
		if (m_isStreaming)
		{
			//�o�b�t�@�����O�J�n
			m_waveFile->ResetFile();
			StartStreamingBuffring();
			m_sourceVoice->Start(0, 0);
		}
		else
		{
			m_sourceVoice->FlushSourceBuffers();
			m_sourceVoice->Start(0);
			Play(m_waveFile->GetReadBuffer(), m_waveFile->GetSize());
		}
		m_isPlaying = true;
	}
	m_isLoop = isLoop;
	m_IsDeleteOnOneShot = IsDelete;
}

void SoundSource::UpdateStreaming()
{
	if (!m_isPlaying)
	{
		return;
	}
	if (m_streamingState == EnStreamingStatus::enStreamingBuffering)
	{
		//�o�b�t�@�����O��
		if (m_waveFile->IsReadEnd())
		{
			//�o�b�t�@�����O���I�����
			m_streamingState = EnStreamingStatus::enStreamingQueueing;
		}
	}
	if (m_streamingState == EnStreamingStatus::enStreamingQueueing)
	{
		//�L���[�C���O��
		XAUDIO2_VOICE_STATE state;
		m_sourceVoice->GetState(&state);
		if (state.BuffersQueued <= 2)
		{
			//�L���[�C���O����Ă���o�b�t�@��2�ȉ��ɂȂ�����L���[�C���O�ł���
			char* buff = m_waveFile->GetReadBuffer();
			Play(&buff[m_readStartPos], m_currentBufferingSize);
			if (m_currentBufferingSize == 0)
			{
				//�ǂݍ��񂾃T�C�Y��0�Ƃ������Ƃ͖��[�܂œǂݍ��݂��I������Ƃ�������
				if (m_isLoop)
				{
					//���[�v����
					//wave�t�@�C���̓ǂݍ��݈ʒu�����Z�b�g���ăo�b�t�@�����O�ĊJ
					m_waveFile->ResetFile();
					StartStreamingBuffring();
				}
				else
				{
					//���[�v���Ȃ��ꍇ�̓L���[����ɂȂ����炳���������イ��傤
					if (state.BuffersQueued == 0)
					{
						//�Đ��I��
						m_isPlaying = false;
						if (m_IsDeleteOnOneShot)
						{
							DeleteGO(this);
							Remove3DSound();
						}
					}
				}
			}
			else
			{
				//�����o�b�t�@�����O����
				StartStreamingBuffring();
			}
		}
	}
}

void SoundSource::Remove3DSound()
{
	if (m_is3DSound)
	{
		g_engine->GetSoundEngine().Remove3DSoundSource(this);
		m_is3DSound = false;
	}
}

void SoundSource::UpdateOnMemory()
{
	if (!m_isPlaying)
	{
		return;
	}
	XAUDIO2_VOICE_STATE state;
	m_sourceVoice->GetState(&state);
	if (state.BuffersQueued <= 0)
	{
		m_isPlaying = false;
		if (m_isLoop)
		{
			//���[�v
			Play(m_isLoop);
		}
		else
		{
			if (m_IsDeleteOnOneShot)
			{
				DeleteGO(this);
				Remove3DSound();
			}
		}
	}
}

void SoundSource::Update()
{
	if (m_isAvailable == false)
	{
		return;
	}

	if (m_isStreaming)
	{
		//�X�g���[�~���O�Đ����̍X�V����
		UpdateStreaming();
	}
	else
	{
		//�I���������Đ����̍X�V����
		UpdateOnMemory();
	}
	if (m_is3DSound == true)
	{
		//�����̈ړ����x���X�V
		m_velocity.Subtract(m_position, m_lastFramePosition);
		m_velocity.Div(g_gameTime.GetFrameDeltaTime());
		m_lastFramePosition = m_position;
	}
}