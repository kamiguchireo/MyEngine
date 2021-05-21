#pragma once
#include "IPlayer.h"

class PlayerStateAim:public IPlayer
{
public:
	PlayerStateAim(Player* pl) :IPlayer(pl) {}
	~PlayerStateAim();
	//�������֐�
	void Init();
	//���������Ȃ��鏈��
	void WaistBend();
	//�X�V����
	void Update();


private:
	//��]�̍X�V
	void UpdateRotation();

private:
	Skeleton* m_plSkeleton = nullptr;
	int m_LeftArmBoneNum = -1;		//���r�̃{�[���ԍ�
	int m_RightArmBoneNum = -1;		//�E�r�̃{�[���ԍ�
};

