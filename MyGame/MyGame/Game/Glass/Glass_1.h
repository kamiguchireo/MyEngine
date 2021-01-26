#pragma once
class Glass_1:public IGameObject
{
public:
	Glass_1();
	~Glass_1();

	bool Start();
	void Update();
	void Draw();

private:
	Model m_Glass;
	ModelInitData m_InitData;
};