#pragma once
#include "IGameCamera.h"
#include "CameraStateTPS.h"
#include "CameraStateAim.h"

enum class CameraState {
	TPS,
	AIM,
};
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void Update();

	void ChangeState(IGameCamera* state)
	{
		currentState = state;
	}

	//�J�����̋�����ݒ�
	void SetCameraDist(float f)
	{
		TPScameraState.SetCameraDist(f);
	}

	//�J�����̃X�e�[�g��ݒ�
	void SetCameraState(CameraState state)
	{
		m_StateNum = state;
	}

	//�v�Z�̋N�_�ƂȂ�ʒu���Z�b�g
	void SetPivotPos(const Vector3& pos)
	{
		m_pivotPos = pos;
	}

private:
	CameraState m_StateNum = CameraState::TPS;
	IGameCamera* currentState = nullptr;
	CameraStateTPS TPScameraState;
	CameraStateAim AIMcameraState;
	Vector3 m_up = Vector3::Up;			//�J�����̏����
	float rot = 0.0f;			//��]��
	float AddPosY = 50.0f;		//�|�W�V�����ɉ��Z���������̒l
	Vector3 m_pivotPos = { 0.0f,0.0f,0.0f };
};