#pragma once
class LevelMatrix
{
public: 
	LevelMatrix(){}
	~LevelMatrix() {}

	void AddMatrix(const Matrix& mat)
	{
		m_LevelMatrixs[MatNum] = mat;
		MatNum++;
	}

	Matrix* GetWorldMatrix()
	{

	}
private:
	std::unique_ptr<Matrix[]>	m_LevelMatrixs;		//���x���̃��[���h�s��
	int MatNum = 0;
};

