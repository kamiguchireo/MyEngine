#pragma once
class SoundSource;

class GameOver:public IGameObject
{
private:
	enum DeadProcess
	{
		enProcess_PlaySound,
		enProcess_CameraMove,
		enProcess_SelectScene,
		enProcess_Fade,
		enProcess_WithoutAlpha,
		enProcess_SceneTrans,
		enProcess_Num,
	};
public:
	GameOver();
	~GameOver();

	void Init(Vector3 pos, Vector3 forward);
	void OnDestroy();
	bool Start();
	void Update();

	//�V���O���g��
	static GameOver* GetInstance()
	{
		if (m_Instance != nullptr)
		{
			return m_Instance;
		}
		return nullptr;
	}
private:
	static GameOver* m_Instance;		//�C���X�^���X
	prefab::SpriteRender* m_DeadSprite = nullptr;		//���S���ɕ\������X�v���C�g
	SoundSource* m_DeadSound = nullptr;
	float m_DeadSpriteAlpha = 0.0f;
	const float m_DeadAlphaFadeSpeed = 0.2f;
	Vector3 m_DeadAfterCameraPos = Vector3::Zero;
	Vector3 m_DeadAfterCameraTarget = Vector3::Zero;
	Vector3 m_LerpForwardCameraPos = Vector3::Zero;
	const float m_DeadCameraDist = 300.0f;		//���S��ɃJ��������������
	float m_DeadAfterLeapSpeed = 0.2f;		//���`�⊮���鑬�x
	float m_DeadLeapTime = 0.0f;		//�⊮����
	Vector3 m_forward = Vector3::Zero;		//�O
	Vector3 m_pos = Vector3::Zero;		//�|�W�V����
	bool m_IsInited = false;		//�������t���O
	int m_process = DeadProcess::enProcess_Num;		//�v���Z�X
};

