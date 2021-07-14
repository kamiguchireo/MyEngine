#include "stdafx.h"
#include "Enemy.h"
#include "SourceFile/Physics/CharacterController.h"
#include "Game/Camera/GameCamera.h"
#include "Game/Stage/Path.h"
#include "Game/Weapon.h"
#include "EnemyHitBox.h"
#include "IEnemy.h"
#include "EnemyStateIdle.h"
#include "EnemyStateMove.h"
#include "EnemyStateAim.h"
#include "Game/Player/Player.h"
#include "EnemyRayTest.h"
#include <random>

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::OnDestroy()
{
	//���f�������_�[
	if (m_enemyModel != nullptr)
	{
		DeleteGO(m_enemyModel);
		m_enemyModel = nullptr;
	}
	//�ҋ@�X�e�[�g
	if (m_stateIdle != nullptr)
	{
		delete m_stateIdle;
		m_stateIdle = nullptr;
	}
	//�ړ��X�e�[�g
	if (m_stateMove != nullptr)
	{
		delete m_stateMove;
		m_stateMove = nullptr;
	}
	if (m_stateAim != nullptr)
	{
		delete m_stateAim;
		m_stateAim = nullptr;
	}
	//����
	if (m_weapon != nullptr)
	{
		DeleteGO(m_weapon);
		m_weapon = nullptr;
	}
	//�q�b�g�{�b�N�X
	if (m_HitBox != nullptr)
	{
		DeleteGO(m_HitBox);
		m_HitBox = nullptr;
	}
	if (characon != nullptr)
	{
		delete characon;
		characon = nullptr;
	}
}

bool Enemy::Start()
{
	//�G�l�~�[�̃X�e�[�^�X
	m_Status = std::make_unique<EnemyStatus>(this);

	//�X�e�[�g��new
	m_stateIdle = new EnemyStateIdle(this);
	m_stateMove = new EnemyStateMove(this);
	m_stateAim = new EnemyStateAim(this);
	characon = new CharacterController();
	ChangeState(m_stateIdle);

	if (m_path != nullptr)
	{
		m_PassPos = m_path->GetPosition();
	}
	else
	{
		m_PassPos.push_back(m_pos);
		m_PassPos.push_back(Vector3{ 300.0f,0.0f,100.0f });
		m_PassPos.push_back(Vector3{ 100.0f,0.0f,100.0f });
		m_PassPos.push_back(Vector3{ 100.0f,0.0f,-1000.0f });

	}

	m_PassSize = static_cast<int>(m_PassPos.size()) - 1;

	m_RayTest = std::make_unique<EnemyRayTest>(this);

	//�v���C���[�̃C���X�^���X���擾
	m_player = Player::GetInstance();

	//�|�W�V�������p�X��0�Ԗڂɍ��킹��
	if (m_PassPos.size() >= 1)
	{
		m_pos = m_PassPos[0];
	}
	//�L�����R���̏�����
	characon->Init(15.0f, 115.0f, m_pos);
	characon->GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Enemy);

	//�ҋ@��Ԃ̃A�j���[�V����
	m_animClip[enEnemyAnimation_Rifle_Idle].Load("Assets/animData/Rifle_Idle.tka");
	m_animClip[enEnemyAnimation_Rifle_Idle].SetLoopFlag(true);
	//������Ԃ̃A�j���[�V����
	m_animClip[enEnemyAnimation_Rifle_Walk].Load("Assets/animData/Rifle_Walk.tka");
	m_animClip[enEnemyAnimation_Rifle_Walk].SetLoopFlag(true);
	//�����Ԃ̃A�j���[�V����
	m_animClip[enEnemyAnimation_Rifle_Run].Load("Assets/animData/Rifle_Run.tka");
	m_animClip[enEnemyAnimation_Rifle_Run].SetLoopFlag(true);
	//�X�v�����g��Ԃ̃A�j���[�V����
	m_animClip[enEnemyAnimation_Rifle_Sprint].Load("Assets/animData/Rifle_Sprint.tka");
	m_animClip[enEnemyAnimation_Rifle_Sprint].SetLoopFlag(true);
	//�G�C����Ԃ̃A�j���[�V����
	m_animClip[enEnemyAnimation_Rifle_Down_To_Aim].Load("Assets/animData/Rifle_Down_To_Aim.tka");
	m_animClip[enEnemyAnimation_Rifle_Down_To_Aim].SetLoopFlag(false);
	//���S���̃A�j���[�V����
	m_animClip[enEnemyAnimation_Death_From_Front].Load("Assets/animData/Death_From_Front.tka");
	m_animClip[enEnemyAnimation_Death_From_Front].SetLoopFlag(false);

	//�G�l�~�[�̃��f����NewGO
	m_enemyModel = NewGO<prefab::ModelRender>(0);
	//���f���̊e��ݒ�
	m_enemyModel->SetTkmFilePath("Assets/modelData/soldier_bs01.tkm");
	m_enemyModel->SetVSEntryPoint("VSMainSkin");
	m_enemyModel->SetSkeleton(m_skeleton);
	m_scale *= 0.8f;
	m_enemyModel->SetScale(m_scale);
	m_enemyModel->SetShadowRecieverFlag(true);

	//�X�P���g���ƃA�j���[�V�����̏�����
	m_skeleton.Init("Assets/modelData/soldier_bs01.tks");
	m_skeleton.Update(Matrix::Identity);
	m_animation.Init(m_skeleton, m_animClip, enEnemyAnimation_Num);
	m_animation.Play(enEnemyAnimation_Rifle_Idle);
	m_rot.SetRotationDegY(0.0f);

	//�����NewGO��Init
	m_weapon = NewGO<Weapon>(1);
	m_weapon->Init(&m_skeleton);

	m_HitBox = NewGO<EnemyHitBox>(2);
	m_HitBox->Init(&m_skeleton, this);

	//�����̎�̕ύX
	std::random_device rnd;
	srand(rnd());

	return true;
}

void Enemy::ChangeNextPass()
{
	if (NextPass < m_PassSize)
	{
		NextPass++;
	}
	else
	{
		NextPass = 0;
	}
}

bool Enemy::CanSeePlayer()
{
	//�݂��ɑ傫��1�̃x�N�g���Ȃ̂œ��ς������cos�Ƃ��c��
	ToPlayerAngle = Dot(ToPlayer, m_moveVec);
	//cos����p�x�����߂�
	ToPlayerAngle = acosf(ToPlayerAngle);
	//���W�A���P�ʂ���f�B�O���[�P�ʂɕϊ�
	ToPlayerAngle = Math::RadToDeg(ToPlayerAngle);
	//�p�x��70�x�ȉ��̎�
	if (ToPlayerAngle <= EnemyAngle)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::DeadProcess()
{
	//���Ɏ���ł���ꍇ
	if (m_animation.IsPlaying())
	{
		//�A�j���[�V�������I����Ă��Ȃ��ꍇ
		//���S���̃A�j���[�V�����𗬂�
		m_animation.Play(enEnemyAnimation_Death_From_Front);
		m_animation.Update(g_gameTime.GetFrameDeltaTime());
		//�q�b�g�{�b�N�X���c���Ă���Ƃ��폜
		if (m_HitBox != nullptr)
		{
			DeleteGO(m_HitBox);
			m_HitBox = nullptr;
		}
		//�L�����R�����c���Ă���Ƃ��폜
		if (characon != nullptr)
		{
			delete characon;
			characon = nullptr;
		}
		//m_weapon->StopFireSound();
	}
}

void Enemy::Update()
{
	if (IsDead == true)
	{
		//���S���̏���
		DeadProcess();
		return;
	}

	float DeltaTime = g_gameTime.GetFrameDeltaTime();

	//�v���C���[�ւ̕���
	ToPlayer = m_player->GetPosition() - m_pos;
	float ToPlayerLength = ToPlayer.Length();
	ToPlayer.Normalize();

	//���C�e�X�g���A�b�v�f�[�g
	if (ToPlayerLength <= 3000.0f)
	{
		m_RayTest->Update(m_player->GetPosition());
	}

	//�v���C���[�𔭌����Ă���Ƃ�
	if (m_ActState == EnemyActState::enState_Discover)
	{
		//���Ԃ����Z
		NowTime_Rand += DeltaTime;
		if (NowTime_Rand >= WaitTime_Rand)
		{	
			//��莞�Ԃ���
			if (RandRange >= RandRangeMin)
			{
				//�Œ�l���l���傫���ꍇ�Ɍ��Z����
				RandRange -= ChangeRandRange;
				NowTime_Rand = 0.0f;
			}
		}
		//�v���C���[�̕����֌�����
		//�Ō�Ƀv���C���[�������ꏊ���X�V
		LastPlayerPos = m_player->GetPosition();
		m_moveVec = LastPlayerPos - m_pos;
		m_moveVec.Normalize();
		m_animation.Play(enEnemyAnimation_Rifle_Idle,0.3f);

		//����̃|�W�V�������Ƃ��Ă���
		Vector3 WeaponPos = m_skeleton.GetBone(m_skeleton.GetWeaponBoneNum())->GetPosition();
		//����̃|�W�V�������Ǝ����Ƀ��C���������Ă��܂��̂ŏ����O�ɏo��
		WeaponPos += ToPlayer * 25.0f;

		int AddRandPos = rand();
		//�v���C���[�ɉ��Z����l���v���X���}�C�i�X�����߂�
		int RandDir = rand();
		//�͈͂����߂�
		AddRandPos %= RandRange;
		//0��1��2���ɂ���
		RandDir %= 2;

		float AddPlayerPos[3] = { 0.0f };
		for (int i = 0; i < 3; i++)
		{
			if (RandDir == 0)
			{
				AddPlayerPos[i] = AddRandPos;
			}
			else
			{
				AddPlayerPos[i] = -AddRandPos;
			}
		}
		Vector3 ToPlayerRand = Vector3::Zero;
		ToPlayerRand = m_player->GetPosition();
		ToPlayerRand.x += AddPlayerPos[0];
		ToPlayerRand.y += AddPlayerPos[1];
		ToPlayerRand.z += AddPlayerPos[2];

		ToPlayerRand -= m_pos;
		ToPlayerRand.Normalize();
		//���C�̎n�_�ƕ������Z�b�g
		m_weapon->SetRay(WeaponPos, ToPlayerRand);
		//�ˌ�
		m_weapon->shooting();
	}
	else if (m_ActState == EnemyActState::enState_vigilant)
	{
		//�Ō�Ƀv���C���[�������ꏊ�Ɉړ�
		m_moveVec = LastPlayerPos - m_pos;
		m_moveVec.Normalize();
	}
	else
	{
		//m_weapon->StopFireSound();
		//���Ԃ����Z
		NowTime_Rand += DeltaTime;
		if (NowTime_Rand >= WaitTime_Rand)
		{
			//��莞�Ԃ���
			if (RandRange <= RandRangeMax)
			{
				//�Œ�l���l���傫���ꍇ�Ɍ��Z����
				RandRange += ChangeRandRange;
				NowTime_Rand = 0.0f;
			}
		}

		//���̃p�X�ւ̃x�N�g��
		m_moveVec = m_PassPos[NextPass] - m_pos;
		//���̃p�X�ւ̋��������ȓ��Ȃ�
		if (m_moveVec.Length() <= PassDist)
		{
			//�ړI�n�̒������̂�
			//���݂̃p�X��ύX
			CurrentPass = NextPass;
		}

		if (CurrentPass == NextPass)
		{
			//���̏�Œ�~����
			IsStop = true;
			//�ҋ@�X�e�[�g�ɕύX
			ChangeState(m_stateIdle);
			//���̃p�X��ύX
			ChangeNextPass();
		}
		if (IsStop == false)
		{
			ChangeState(m_stateMove);
		}

		//���̃p�X�ւ̃x�N�g��
		m_moveVec.y = 0.0f;
		m_moveVec.Normalize();
	}

	//��]��K�p
	m_rot.SetRotation(Vector3::AxisZ, m_moveVec);

	//�A�j���[�V��������footstep�̈ړ��ʂ������Ă���
	footStepValue = m_animation.Update(DeltaTime);

	//Max�Ƃ͎����Ⴄ�̂Ŏ������킹��
	float value = footStepValue.y;
	footStepValue.y = footStepValue.z;
	footStepValue.z = -value;

	//�t�b�g�X�e�b�v�𒲐�
	//�X�P�[���̒l���Ƃ�
	footStepValue *= m_scale.x;

	//�d�͂����Z
	if (characon->IsOnGround())
	{
		//�n�ʏ�ɂ���Ƃ��͏d�͂����Z�b�g
		m_gravity *= 0.0f;
	}
	else
	{
		//�󒆂ɂ���Ƃ��͏d�͂����Z��������
		m_gravity += gravity;
	}

	footStepValue += m_gravity;

	//���݂̃X�e�[�g�̍X�V
	if (m_ActState == EnemyActState::enState_Normal)
	{
		currentState->Update();
	}

	//footStep�ɉ�]��K��
	m_rot.Apply(footStepValue);

	//�L�����R���̌v�Z
	Vector3 returnPos = characon->Execute(footStepValue);

	m_pos = returnPos;

	m_enemyModel->SetPosition(m_pos);
	m_enemyModel->SetRotation(m_rot);
}