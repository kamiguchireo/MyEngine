#pragma once

class Level;
class Grass_03;
class Tree1;
class Tree2;
class Bush_02;
class Path;
class SoundSource;
class Player;
class Enemy;
class ReadLevelObj;
class Stage :public IGameObject
{
public:
	Stage();
	~Stage();

	void OnDestroy();
	bool Start();
	void Update();
private:
	std::unique_ptr<ReadLevelObj> m_readobj;
	Level* m_level = nullptr;
	Grass_03* m_Glass = nullptr;
	Tree1* m_Tree1 = nullptr;
	Tree2* m_Tree2 = nullptr;
	Bush_02* m_Bush = nullptr;
	SoundSource* m_BirdSound = nullptr;
	SoundSource* m_BreezeSound = nullptr;
	Player* m_Player = nullptr;
	std::vector<Path*> m_Path;
	std::vector<Enemy*>m_enemy;
	//bool m_IsPathInited[100] = { false };
	//bool m_IsEnemyInited[100] = { false };
	//int m_numEnemy = 0;
	//int Firstplace = 0;
	//int Tenthplace = 0;
	//int m_numPath = 0;
	int time = 0;
	bool m_IsInited = false;
};