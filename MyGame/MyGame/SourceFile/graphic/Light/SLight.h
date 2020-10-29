#pragma once
#include "stdafx.h"
const int NUM_DIRECTIONAL_LIGHT = 4;	//�f�B���N�V�������C�g�̐��B

namespace Engine {
	/// �f�B���N�V�������C�g�B
	struct DirectionalLight {
		Vector3 direction = Vector3::Right;	//���C�g�̕����B
		float pad0 = 0.0f;			//�p�f�B���O�B
		Vector4 color = {0.0f,0.0f,0.0f,0.0f};		//���C�g�̃J���[�B
	};
	/// ���C�g�\���́B
	struct Light {
		DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];	//�f�B���N�V�������C�g�B
		Vector3 eyePos = Vector3::Zero;					//�J�����̈ʒu�B
		float specPow = 5.0f;					//�X�y�L�����̍i��B
		Vector3 ambinetLight = Vector3::One;			//�����B
	};
}