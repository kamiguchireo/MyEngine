#include "stdafx.h"
#include "Pass.h"

Pass*Pass::instance = nullptr;

Pass::Pass()
{
	//�C���X�^���X�Ɏ������g������
	instance = this;
}