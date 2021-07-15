#pragma once
class GameOver:public IGameObject
{
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
	prefab::SpriteRender* m_DiedSprite = nullptr;		//���S���ɕ\������X�v���C�g
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
};

