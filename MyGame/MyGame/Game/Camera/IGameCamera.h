#pragma once
//�Q�[���J�����̃C���^�[�t�F�[�X�N���X
class IGameCamera
{
public:
	IGameCamera(){}
	virtual ~IGameCamera()
	{

	}

	virtual void Update(Vector3& pos, Vector3& target) = 0;
};

