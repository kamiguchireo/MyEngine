#pragma once
#include "IGameCamera.h"

class CameraStateTPS :public IGameCamera
{
public:
	CameraStateTPS();
	~CameraStateTPS();

	void Update(Vector3& pos, Vector3& target);

private:
	float CameraDist = 300.0f;			//�J��������^�[�Q�b�g�܂ł̋���
	float rot = 0.0f;			//��]��
};

