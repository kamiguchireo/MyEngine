#pragma once
#include "IGameCamera.h"

class CameraStateAim:public IGameCamera
{
public:
	CameraStateAim();
	~CameraStateAim();

	void Update(Vector3& pivotpos,float& rot);
	void SetAddPosY(float* f)
	{
		AddPosY = f;
	}
private:
	float CameraDist = 200.0f;			//�J��������^�[�Q�b�g�܂ł̋���
	//float rot = 0.0f;			//��]��
	float* AddPosY = nullptr;		//�|�W�V�����ɉ��Z���������̒l
	const float MaxAddPos = 150.0f;		//�|�W�V�����ɉ��Z�ł��������̍ő�l
	const float MinAddPos = -150.0f;		//�|�W�V�����ɉ��Z�ł��������̍ŏ��l
	const float DefaultCameraHeight = 130.0f;		//�J�����̃f�t�H���g�̍���
	int DefaultPoint[2] = { 500,300 };
	float sensiX = 0.00025f;
	float sensiY = 0.1f;
};

