#pragma once

class Stage;
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
	bool IsDestroyObject = false;
};