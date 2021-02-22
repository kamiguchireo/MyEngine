#pragma once
#include "IGameCamera.h"

class CameraStateAim:public IGameCamera
{
public:
	CameraStateAim();
	~CameraStateAim();

	void Update(Vector3& /*pos*/, Vector3& target);

};

