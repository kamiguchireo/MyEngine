#pragma once
#include "stdafx.h"

namespace Engine {
	/// �f�B���N�V�������C�g�B
	struct DirectionalLight {
		Vector3 direction;	//���C�g�̕����B
		float pad0;			//�p�f�B���O�B
		Vector4 color;		//���C�g�̃J���[�B
	};
}