#pragma once
#include "IGameCamera.h"
#include "CameraCollisionSolver.h"

class CameraStateTPS :public IGameCamera
{
public:
	CameraStateTPS();
	~CameraStateTPS();

	void Update(Vector3& pos, Vector3& target,float& rot);
	void SetCameraDist(float f)
	{
		CameraDist = f;
	}
	void SetAddPosY(float* f)
	{
		AddPosY = f;
	}
private:
	float CameraDist = 200.0f;			//�J��������^�[�Q�b�g�܂ł̋���
	float* AddPosY = nullptr;		//�|�W�V�����ɉ��Z���������̒l
	const float MaxAddPos = 150.0f;		//�|�W�V�����ɉ��Z�ł��������̍ő�l
	const float MinAddPos = -50.0f;		//�|�W�V�����ɉ��Z�ł��������̍ŏ��l
	POINT pt = { 0,0 };
	int DefaultPoint[2] = { 500,300 };
	float sensiX = 0.00025f;
	float sensiY = 0.1f;
	CameraCollisionSolver m_cameraCollisionSolver;
	float Col_Radius = 5.0f;		//�X�t�B�A�R���C�_�[�̔��a
};

