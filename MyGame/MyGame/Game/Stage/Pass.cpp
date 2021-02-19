#include "stdafx.h"
#include "Pass.h"

Pass*Pass::instance = nullptr;

Pass::Pass()
{
	//インスタンスに自分自身を入れる
	instance = this;
}