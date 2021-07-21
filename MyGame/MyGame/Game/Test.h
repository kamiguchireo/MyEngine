#pragma once

class Level;
class Player;
class Test:public IGameObject
{
public:
	Test();
	~Test();

	void OnDestroy();
	bool Start();
	void Update();
private:
	Level* m_level = nullptr;
	Player* m_player = nullptr;
};