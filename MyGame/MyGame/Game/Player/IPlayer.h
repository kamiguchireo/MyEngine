#pragma once
#include "SourceFile/graphic/ModelRender.h"

//�v���C���[�̊��N���X
class IPlayer
{
public:
	IPlayer();
	virtual ~IPlayer()
	{
	}
	//�X�V�֐�
	virtual void Update(Vector3& pos,Quaternion& rot,Vector3& scale) = 0;

};

