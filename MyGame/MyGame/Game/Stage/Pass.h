#pragma once
class Pass
{
public:
	Pass();
	~Pass(){}

	//パスの追加
	void AddPosition(const Vector3& pos)
	{
		m_position.push_back(pos);
	}

	static Pass* GetInstance()
	{
		return instance;
	}

	std::vector<Vector3>& GetPosition()
	{
		return m_position;
	}
private:
	std::vector<Vector3> m_position;		//Passのポジション
	static Pass* instance;
};