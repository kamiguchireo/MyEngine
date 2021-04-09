#pragma once
//ゲームカメラのインターフェースクラス
class IGameCamera
{
public:
	IGameCamera(){}
	virtual ~IGameCamera()
	{

	}

	virtual void Update(Vector3& pivotpos, float& rot) = 0;
	virtual void SetAddPosY(float* f) {}
};

