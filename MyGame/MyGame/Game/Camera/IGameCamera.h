#pragma once
//ゲームカメラのインターフェースクラス
class IGameCamera
{
public:
	IGameCamera(){}
	virtual ~IGameCamera()
	{

	}

	virtual void Update(Vector3& pos, Vector3& target) = 0;
};

