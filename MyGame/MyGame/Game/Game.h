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
	static Game* m_Instance;		//インスタンス
	Title* m_Title = nullptr;		//タイトル
	Stage* m_Stage_01 = nullptr;		//ステージ
	GameOver* m_GameOver = nullptr;		//ゲームオーバー
	GameClear* m_GameClear = nullptr;		//ゲームクリアー
	int m_SceneNum = SceneNum::enScene_Num;		//現在のシーン番号
	bool IsDirty = true;
	bool IsStageInited = true;
	int EnemyCount = 0;
};