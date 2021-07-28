#pragma once
#include "SourceFile/Physics/CharacterController.h"
#include "Game/Weapon.h"
#include "SourceFile/Graphic/SpriteRender.h"
#include "PlayerStatus.h"
#include "SourceFile/sound/SoundSource.h"
#include "Game/Camera/GameCamera.h"

class IPlayer;
class GameCamera;
class PlayerStateIdle;
class PlayerStateMove;
class PlayerStateAim;
class PlayerHitBox;
class Player:public IGameObject
{
public:
	Player();
	~Player();

	void OnDestroy();
	bool Start();
	void Update();

	//�|�W�V���������Z
	void AddPosition(Vector3 pos)
	{
		m_pos += pos;
	}

	//�A�j���[�V�������Đ�
	void PlayAnimation(int i)
	{
		m_animation.Play(i,0.3f);
	}

	//�A�j���[�V�������X�V
	void UpdateAnimation(float f)
	{
		m_animation.Update(f);
	}

	//�|�W�V�������Z�b�g
	void SetPosition(const Vector3& pos)
	{
		m_pos = pos;
	}
	//��]���Z�b�g
	void SetRotation(const Quaternion& rot)
	{
		m_rot = rot;
	}
	//�X�P�[�����Z�b�g
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	//���ʂ��Q�b�g
	Vector3 GetForward()const
	{
		return m_forward;
	}

	//���ʂ��Z�b�g
	void SetForward(Vector3 vec)
	{
		m_forward = vec;
	}
	//�E�������Z�b�g
	void SetRight(Vector3 vec)
	{
		m_right = vec;
	}
	//����p�̍s����Q�b�g
	const Matrix& GetWeaponBoneMat()
	{
		return m_skeleton.GetWeaponMatrix();
	}

	//�f�J�[����ǉ�
	bool Shooting()
	{
		if (m_PlayerWeapon != nullptr)
		{
			Vector3 Direction = g_camera3D->GetTarget() - g_camera3D->GetPosition();
			Direction.Normalize();
			auto bone = m_skeleton.GetBone(m_skeleton.GetWeaponBoneNum());
			Vector3 weaponpos = bone->GetPosition();
			Vector3 CameraToWeaponPos = g_camera3D->GetPosition() - weaponpos;
			float length = CameraToWeaponPos.Length();
			Vector3 pos = g_camera3D->GetPosition();
			pos += Direction * length;
			m_PlayerWeapon->SetRay(pos, Direction);
			return m_PlayerWeapon->shooting();
		}
		return false;
	}

	bool IsWeaponAvailable()
	{
		return m_PlayerWeapon->IsAvailable();
	}

	void WeaponRelease()
	{
		m_PlayerWeapon->Release();
	}
	//���S
	void Dead()
	{
		//���S���̃A�j���[�V�����𗬂�
		m_animation.Play(enPlayerAnimation_Death_From_Front);
		IsDead = true;
	}

	//�_���[�W���󂯂�
	void Damage(int i)
	{
		m_Status->Damage(i);
	}

	//�X�P���g�����Q�b�g
	Skeleton* GetSkeleton()
	{
		return &m_skeleton;
	}

	//�V���O���g��
	static Player* GetInstance()
	{
		if (m_Instance != nullptr)
		{
			return m_Instance;
		}
		return nullptr;
	}
	const Vector3 GetPosition()const
	{
		return m_pos;
	}

	void ChangeCameraStateTPS()
	{
		m_camera->SetCameraState(CameraState::TPS);
	}
private:
	//�X�e�[�g�̕ύX
	//state		�X�e�[�g
	void ChangeState(IPlayer* state)
	{
		currentState = state;
	}
	
	//�ړ��̏���
	void Move();

	//���ϊ�
	void AxisTrans();

	//�\���鏈��
	void Hold();

	//���S���̏���
	void DeadProcess();

private:
	static Player* m_Instance;		//�C���X�^���X
	IPlayer* currentState = nullptr;		//���݂̃X�e�[�g
	prefab::ModelRender* m_playerModel = nullptr;		//�v���C���[�̃��f��
	Skeleton m_skeleton;		//�X�P���g��
	Engine::Animation m_animation;		//�A�j���[�V����
	Engine::AnimationClip m_animClip[enPlayerAnimation_Num];		//�A�j���[�V�����N���b�v
	Vector3 m_pos = {0.0f,50.0f,-1700.0f};		//�|�W�V����
	Vector3 m_scale = { 0.8f,0.8f,0.8f };		//�X�P�[��
	Quaternion m_rot = Quaternion::Identity;		//�L�����N�^�[�̉�]
	PlayerStateIdle* m_stateIdle = nullptr;		//�ҋ@���
	PlayerStateMove* m_stateMove = nullptr;		//�ړ����
	PlayerStateAim* m_stateAim = nullptr;		//�G�C�����
	Weapon* m_PlayerWeapon = nullptr;		//�v���C���[�̕���
	GameCamera* m_camera = nullptr;		//�J����
	Vector3 m_forward = Vector3::Front;		//�O����
	Vector3 m_right = Vector3::Right;		//�E����
	CharacterController* characon = nullptr;		//�L�����R��
	Vector3 footStepValue = Vector3::Zero;		//footStep�̈ړ���
	prefab::SpriteRender* m_AimFramesprite = nullptr;		//�G�C�����ɕ\������X�v���C�g
	Vector3 m_gravity = Vector3::Zero;		//�d�͂ɂ�����
	PlayerHitBox* m_HitBox = nullptr;
	bool IsDead = false;		//����ł��邩�ǂ���
	int m_HeadBoneNum = -1;
	std::unique_ptr<PlayerStatus> m_Status = nullptr;
	SoundSource* m_HoldRifleSound = nullptr;		//�e���\����Ƃ��̃T�E���h
	bool IsRightClick = false;
	bool IsAim = false;

};