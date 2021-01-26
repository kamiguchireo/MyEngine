#pragma once
class Glass_1:public IGameObject
{
public:
	Glass_1();
	~Glass_1();

	bool Start();
	void Update();
	void Draw();

	void AddInstance()
	{
		m_instanceNum++;
	}
private:
	Model m_Glass;
	ModelInitData m_InitData;
	int m_instanceNum = 1;		//インスタンスの数
};