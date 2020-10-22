#pragma once
#include "stdafx.h"
const int NUM_DIRECTIONAL_LIGHT = 4;	//�f�B���N�V�������C�g�̐��B

namespace Engine {
	/// �f�B���N�V�������C�g�B
	struct DirectionalLight {
		Vector3 direction;	//���C�g�̕����B
		float pad0;			//�p�f�B���O�B
		Vector4 color;		//���C�g�̃J���[�B
	};
	/// ���C�g�\���́B
	struct Light {
		DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];	//�f�B���N�V�������C�g�B
		Vector3 eyePos;					//�J�����̈ʒu�B
		float specPow;					//�X�y�L�����̍i��B
		Vector3 ambinetLight;			//�����B
	};
}