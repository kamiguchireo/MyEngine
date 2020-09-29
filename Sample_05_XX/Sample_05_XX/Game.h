#pragma once
class Game
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
	void Draw();

private:
	Model m_unityChan;
	ModelInitData m_unityChanInitData;
	Vector3 pos = Vector3::Zero;
	Vector3 scale = Vector3::One;
	RenderContext RC;
	Light light;
};
