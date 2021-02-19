#pragma once
class Path
{
public:
	Path();
	~Path(){}

	//パスの追加
	void AddPosition(const Vector3& pos)
	{
		m_position.push_back(pos);
	}

	static Path* GetInstance()
	{
		return instance;
	}

	std::vector<Vector3>& GetPosition()
	{
		return m_position;
	}
private:
	std::vector<Vector3> m_position;		//Passのポジション
	static Path* instance;
};