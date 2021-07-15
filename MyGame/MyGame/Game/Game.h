#pragma once

class Stage;
class Title;

enum SceneNum {
	enScene_Title,
	enScene_Stage01,
	enScene_Num,
};

class Game:public IGameObject
{
public:
	Game();
	~Game();
	void OnDestroy();
	bool Start();
	void Update();

	static Game* GetInstance()
	{
		if (m_Instance != nullptr)
		{
			return m_Instance;
		}
		return nullptr;
	}

	void SceneTrans(int scenenum);

private:
	void DeleteScene(int scenenum);
	void NewScene(int scenenum);
private:
	static Game* m_Instance;		//�C���X�^���X
	Title* m_Title = nullptr;		//�^�C�g��
	Stage* m_Stage_01 = nullptr;		//�X�e�[�W
	int m_SceneNum = SceneNum::enScene_Num;		//���݂̃V�[���ԍ�
	bool IsDirty = false;
	bool IsStageInited = false;
};