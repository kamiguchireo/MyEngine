#pragma once
#include "WaveFileBank.h"
#include <xaudio2.h>
#include <x3daudio.h>

class WaveFile;
class SoundSource;
class SoundEngine
{
public:
	SoundEngine();
	~SoundEngine();

	//������
	void Init();

	//���
	void Release();

	//�X�V
	void Update();

	//3D�T�E���h�\�[�X��ǉ�
	void Add3DSoundSource(SoundSource* s)
	{
		m_3dSoundSource.push_back(s);
	}

	//�T�E���h�\�[�X���폜
	void Remove3DSoundSource(SoundSource* s)
	{
		auto it = std::find(m_3dSoundSource.begin(), m_3dSoundSource.end(), s);
		if (it != m_3dSoundSource.end())
		{
			m_3dSoundSource.erase(it);
		}
	}

	//�T�E���h���X�i�[�̍��W��ݒ�
	//3D�������g���Ă���Ƃ��̌v�Z�Ɏg�p����܂�
	void SetListenerPosition(const Vector3& pos)
	{
		m_listenerPosition = pos;
	}

	//�T�E���h���X�i�[�̑O������ݒ�
	//3D�������g���Ă���Ƃ��̌v�Z�Ɏg�p����܂�
	void SetListenerFront(Vector3 front)
	{
		m_listenerFront = front;
	}

	//�T�E���h���X�i�[�̏������ݒ�
	//3D�������g���Ă���Ƃ��̌v�Z�Ɏg�p����܂�
	void SetListenerUp(Vector3 up)
	{
		m_listenerUp = up;
	}

	//XAudio2�̃\�[�X�{�C�X���쐬
	IXAudio2SourceVoice* CreateXAudio2SourceVoice(WaveFile* waveFile, bool is3DSound);
	
	IXAudio2MasteringVoice* GetMasteringVoice()
	{
		return m_masteringVoice;
	}

	IXAudio2SubmixVoice* GetSubmixVoice()
	{
		return m_submixVoice;
	}

	//�o�̓`�����l���̐����擾
	int GetNumChannel()const
	{
		return m_nChannels;
	}

	//�g�`�f�[�^�o���N���擾
	WaveFileBank& GetWaveFileBank()
	{
		return m_waveFileBank;
	}

	//�T�E���h�G���W�������p�\���ǂ�������
	//true���Ԃ��Ă����痘�p�\�ł�
	bool IsAvailable()const
	{
		return m_isInited;
	}

private:
	IXAudio2* m_xAudio2 = nullptr;
	IXAudio2MasteringVoice* m_masteringVoice = nullptr;
	X3DAUDIO_HANDLE m_hx3DAudio;					//!<3D�I�[�f�B�I�̃n���h���B
	IUnknown* m_reverbEffect = nullptr;				//!<���o�[�v�G�t�F�N�g�B
	IXAudio2SubmixVoice* m_submixVoice = nullptr;	//!<�T�u�~�b�N�X�{�C�X�B
	DWORD m_channelMask = 0;						//!<�I�[�f�B�I�`�����l���}�X�N�B
	DWORD m_nChannels = 0;							//!<�`�����l�����B
	Vector3 m_listenerPosition = Vector3::Zero;	//!<���X�i�[�̍��W�B
	Vector3 m_listenerFront = Vector3::Front;		//���X�i�[�̐���
	Vector3 m_listenerUp = Vector3::Up;
	bool m_UseListenerCone = true;
	bool m_fUseInnerRadius = true;		//�����a���g�p���邩
	bool m_useRedirectToLFE = false;		//�d�ቹ����
	bool m_isInited = false;
	X3DAUDIO_LISTENER m_listener;					//!<�T�E���h���X�i�[�B
	std::list<SoundSource*>	m_3dSoundSource;	//!<3D�T�E���h�̃T�E���h�\�[�X�B
	X3DAUDIO_CONE	m_emitterCone;
	WaveFileBank m_waveFileBank;
};

