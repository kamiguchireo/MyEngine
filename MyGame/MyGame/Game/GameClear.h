#pragma once
class GameClear:public IGameObject
{
private:
	enum ClearProcess {
		enProcess_PlaySound,
		enProcess_CameraMove,
		enProcess_SelectScene,
		enProcess_Fade,
		enProcess_WithoutAlpha,
		enProcess_SceneTrans,
		enProcess_Num,
	};

public:
	GameClear();
	~GameClear();

	void Init(Vector3 pos, Vector3 forward);
	void OnDestroy();
	bool Start();
	void Update();
	//�V���O���g��
	static GameClear* GetInstance()
	{
		if (m_Instance != nullptr)
		{
			return m_Instance;
		}
		return nullptr;
	}
private:
	static GameClear* m_Instance;		//�C���X�^���X
	prefab::SpriteRender* m_ClearSprite = nullptr;
	float m_ClearSpriteAlpha = 0.0f;
	Vector3 m_forward = Vector3::Zero;		//�O
	Vector3 m_pos = Vector3::Zero;		//�|�W�V����
	bool m_IsInited = false;		//�������t���O
	int m_process = ClearProcess::enProcess_Num;
};

