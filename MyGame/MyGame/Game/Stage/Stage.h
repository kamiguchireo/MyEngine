#pragma once

class Level;
class Grass_03;
class Tree1;
class Tree2;
class Bush_02;
class Path;
class SoundSource;
class Player;
class Stage
{
public:
	Stage();
	~Stage();
	
private:
	Level* m_level = nullptr;
	Grass_03* m_Glass = nullptr;
	Tree1* m_Tree1 = nullptr;
	Tree2* m_Tree2 = nullptr;
	Bush_02* m_Bush = nullptr;
	Path* m_Path = nullptr;
	SoundSource* m_sound = nullptr;
	Player* m_Player = nullptr;
};

