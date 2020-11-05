#pragma once
//プレイヤーの基底クラス
class IPlayer
{
public:
	//更新関数
	virtual void Update() = 0;

private:
	Vector3 m_pos = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;
};

