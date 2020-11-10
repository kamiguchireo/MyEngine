#pragma once
#include "SourceFile/graphic/ModelRender.h"

//プレイヤーの基底クラス
class IPlayer
{
public:
	IPlayer();
	virtual ~IPlayer()
	{
	}
	//更新関数
	virtual void Update() = 0;

};

