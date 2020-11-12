#pragma once
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void Update();

	void SetTarget(const Vector3& pos)
	{
		m_target = pos;
	}
private:
	Vector3 m_pos = { 0.0f, 100.0f, -300.0f };		//�J�����̎��_
	Vector3 m_target = { 0.0f, 100.0f, 0.0f };		//�J�����̒����_
	Vector3 m_up = Vector3::Up;			//�J�����̏����
};