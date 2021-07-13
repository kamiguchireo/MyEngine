#pragma once
#include "WaveFile.h"

class SoundSource :public IGameObject
{
public:
	SoundSource();
	~SoundSource();

	//初期化
	//オンメモリ再生向け
	void Init(const wchar_t* filePath, bool is3DSound = false);

	//初期化
	//ストリーミング再生向け
	//ringBufferSize		リングバッファのサイズ
	//bufferSize		ストリーミングの最大バッファリングのサイズ
	void InitStreaming(wchar_t* filePath, bool is3DSound = false, unsigned int ringBufferSize = 3 * 1024 * 1024, unsigned int bufferSize = 1024 * 512);

	//解放処理
	void Release();

	//再生
	//isLoop		ループ再生フラグ
	//ワンショット再生の場合再生が完了すると自動的にインスタンスを破棄します
	//ワンショット再生のSoundSourceのインスタンスをメンバ変数で保持していると
	//破棄されたインスタンスにアクセスしてしまう可能性があります
	void Play(bool isLoop,bool IsDelete = true);

	//停止
	void Stop()
	{
		m_sourceVoice->Stop();
		m_isPlaying = false;
	}

	//一時停止
	void Pause()
	{
		m_sourceVoice->Stop();
	}

	//再生中？
	bool IsPlaying()const
	{
		return m_isPlaying;
	}

	//ボリュームを設定
	void SetVolume(float vol)
	{
		m_sourceVoice->SetVolume(vol);
	}

	//ボリュームを取得
	float GetVolume()const
	{
		float vol;
		m_sourceVoice->GetVolume(&vol);
		return vol;
	}

	//音源の座標を設定
	//3Dサウンドの時に必要になります
	//2Dサウンドでは無視されます
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
		if (m_isSetPositionFirst)
		{
			m_lastFramePosition = m_position;
			m_isSetPositionFirst = false;
		}
	}

	//音源の座標を取得
	Vector3 GetPosition()const
	{
		return m_position;
	}

	//音源の移動速度を取得
	Vector3 GetVelocity()const
	{
		return m_velocity;
	}

	//音源の減衰距離を設定
	void SetCurveDistance(float dist)
	{
		m_CurveDistance = dist;
	}
	//音源の減衰距離を取得
	float GetCurveDistance()
	{
		return m_CurveDistance;
	}
	//ループフラグを取得
	bool GetLoopFlag()const
	{
		return m_isLoop;
	}

	//ボイスの周波数調整
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
	//入力チャンネル数を取得。
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
	//ストリーミング再生中の更新処理。
	void UpdateStreaming();
	//オンメモリ再生中の更新処理。
	void UpdateOnMemory();
	void Play(char* buff, unsigned int bufferSize);
	/*!
	* @brief	ストリーミングバッファリングの開始。
	*/
	void StartStreamingBuffring();
	void Remove3DSound();
	/*!
	* @brief	更新。
	*/
	void Update() override;
private:
	enum EnStreamingStatus {
		enStreamingBuffering,	//バッファリング中。
		enStreamingQueueing,	//キューイング中。
	};
	std::shared_ptr<WaveFile>	m_waveFile;					//!<波形データ。
	IXAudio2SourceVoice* m_sourceVoice = nullptr;	//!<ソースボイス。
	bool						m_isLoop = false;			//!<ループフラグ。
	bool						m_isPlaying = false;		//!<再生中フラグ。
	bool					m_isStreaming = false;		//!<ストリーミング再生？
	unsigned int			m_streamingBufferSize = 0;	//!<ストリーミング用のバッファリングサイズ。
	unsigned int			m_currentBufferingSize = 0;	//!<現在のバッファリングのサイズ。
	unsigned int			m_readStartPos = 0;			//!<読み込み開始位置。
	unsigned int			m_ringBufferSize = 0;		//!<リングバッファのサイズ。
	EnStreamingStatus		m_streamingState = enStreamingBuffering;	//!<ストリーミングステータス。
	bool					m_is3DSound = false;		//!<3Dサウンド？
	Vector3				m_position = Vector3::Zero;	//!<音源の座標。3Dサウンドの時に必要。
	Vector3				m_lastFramePosition = Vector3::Zero;//!<音源の1フレーム前の座標。3Dサウンドの時に必要。
	Vector3				m_velocity = Vector3::Zero;	//!<速度。3Dサウンドの時に必要・
	FLOAT32 m_emitterAzimuths[INPUTCHANNELS];
	FLOAT32 m_matrixCoefficients[INPUTCHANNELS * OUTPUTCHANNELS];
	X3DAUDIO_DSP_SETTINGS m_dspSettings;
	bool m_isSetPositionFirst = true;	//!<一番最初のsetPosition?
	bool m_isAvailable = false;			//!<インスタンスが利用可能？
	bool m_IsDeleteOnOneShot = true;
	float m_CurveDistance = 1000.0f;
};