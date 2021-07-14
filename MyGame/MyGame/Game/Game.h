#pragma once

class Stage;
class Title;
class Game:public IGameObject
{
public:
	Game();
	~Game();
	void Destroy();
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

	void SceneTrans();

private:
	void DeleteObject();
	void NewObject();

private:
	static Game* m_Instance;
	Stage* m_Stage = nullptr;		//ステージ
	Title* m_Title = nullptr;
	bool IsDestroyObject = false;
};