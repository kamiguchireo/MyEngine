#pragma once
//�v���C���[�̊��N���X
class IPlayer
{
public:
	//�X�V�֐�
	virtual void Update() = 0;

private:
	Vector3 m_pos = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;
};

