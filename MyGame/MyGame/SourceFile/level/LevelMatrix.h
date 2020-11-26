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
	std::unique_ptr<Matrix[]>	m_LevelMatrixs;		//レベルのワールド行列
	int MatNum = 0;
};

