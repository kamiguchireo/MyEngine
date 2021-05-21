#pragma once
#include "IPlayer.h"

class PlayerStateAim:public IPlayer
{
public:
	PlayerStateAim(Player* pl) :IPlayer(pl) {}
	~PlayerStateAim();
	//初期化関数
	void Init();
	//腰から上を曲げる処理
	void WaistBend();
	//更新処理
	void Update();


private:
	//回転の更新
	void UpdateRotation();

private:
	Skeleton* m_plSkeleton = nullptr;
	int m_LeftArmBoneNum = -1;		//左腕のボーン番号
	int m_RightArmBoneNum = -1;		//右腕のボーン番号
};

