#pragma once
//�Q�[���J�����̃C���^�[�t�F�[�X�N���X
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

