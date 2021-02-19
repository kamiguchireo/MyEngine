#pragma once
class Pass
{
public:
	Pass(){}
	~Pass(){}

	//パスの追加
	void AddPosition(const Vector3& pos)
	{
		m_position.push_back(pos);
	}
private:
	std::vector<Vector3> m_position;		//Passのポジション
};

