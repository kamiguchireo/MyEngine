#pragma once
class Pass
{
public:
	Pass(){}
	~Pass(){}

	//�p�X�̒ǉ�
	void AddPosition(const Vector3& pos)
	{
		m_position.push_back(pos);
	}
private:
	std::vector<Vector3> m_position;		//Pass�̃|�W�V����
};

