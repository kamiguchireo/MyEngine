#pragma once

class Stage;
class Title;
class GameOver;
class GameClear;
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
	void AddEnemyCount()
	{
		EnemyCount++;
	}
	void SubEnemyCount()
	{
		EnemyCount--;
	}
	int GetEnemyCount()
	{
		return EnemyCount;
	}
private:
	void DeleteScene(int scenenum);
	void NewScene(int scenenum);

private:
	static Game* m_Instance;		//�C���X�^���X
	Title* m_Title = nullptr;		//�^�C�g��
	Stage* m_Stage_01 = nullptr;		//�X�e�[�W
	GameOver* m_GameOver = nullptr;		//�Q�[���I�[�o�[
	GameClear* m_GameClear = nullptr;		//�Q�[���N���A�[
	int m_SceneNum = SceneNum::enScene_Num;		//���݂̃V�[���ԍ�
	bool IsDirty = true;
	bool IsStageInited = true;
	int EnemyCount = 0;
};