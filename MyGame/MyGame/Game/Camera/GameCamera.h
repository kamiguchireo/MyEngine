#pragma once
#include "IGameCamera.h"
#include "CameraStateTPS.h"
#include "CameraStateAim.h"

enum class CameraState {
	TPS,
	AIM,
	NUM
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
		if (m_StateNum != state)
		{
			m_StateNum = state;
			switch (m_StateNum)
			{
			case CameraState::TPS:
				//TPS�J�����ɂ���
				ChangeState(&TPScameraState);
				currentState->SetAddPosY(50.0f);
				break;
			case CameraState::AIM:
				//AIM�J�����ɂ���
				ChangeState(&AIMcameraState);
				currentState->SetAddPosY(0.0f);
				break;
			default:
				break;
			}
		}
	}

	//�v�Z�̋N�_�ƂȂ�ʒu���Z�b�g
	void SetPivotPos(const Vector3& pos)
	{
		m_pivotPos = pos;
	}

	void SetHeadPos(const Vector3& pos)
	{
		m_HeadPos = pos;
	}
private:


private:
	CameraState m_StateNum = CameraState::NUM;
	IGameCamera* currentState = nullptr;
	CameraStateTPS TPScameraState;
	CameraStateAim AIMcameraState;
	Vector3 m_up = Vector3::Up;			//�J�����̏����
	float rot = 0.0f;			//��]��
	float AddPosY = 50.0f;		//�|�W�V�����ɉ��Z���������̒l
	Vector3 m_pivotPos = { 0.0f,0.0f,0.0f };
	Vector3 m_HeadPos = Vector3::Zero;
};