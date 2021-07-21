#pragma once

class Level;
class Player;
class Path;
class Enemy;
class ReadLevelObj;
class Test:public IGameObject
{
public:
	Test();
	~Test();

	void OnDestroy();
	bool Start();
	void Update();
private:
	std::unique_ptr<ReadLevelObj> m_readobj;
	Level* m_level = nullptr;
	Player* m_player = nullptr;
	std::vector<Path*> m_Path;
	std::vector<Enemy*>m_enemy;
};