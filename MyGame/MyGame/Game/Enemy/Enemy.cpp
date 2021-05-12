#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	//�G�l�~�[�̃X�e�[�^�X
	m_Status = std::make_unique<EnemyStatus>(this);

	//�X�e�[�g��new
	m_stateIdle = new EnemyStateIdle(this);
	m_stateMove = new EnemyStateMove(this);
	m_stateAim = new EnemyStateAim(this);
	characon = new CharacterController();
	ChangeState(m_stateIdle);

	m_path = Path::GetInstance();
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
}

Enemy::~Enemy()
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
		m_stateMove = nullptr;
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
	//�|�W�V�������p�X��0�Ԗڂɍ��킹��
	if (m_PassPos.size() >= 1)
	{
		m_pos = m_PassPos[0];
	}
	//�L�����R���̏�����
	characon->Init(15.0f, 115.0f, m_pos);

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

void Enemy::Update()
{
	if (IsDead == true)
	{
		m_animation.Play(enEnemyAnimation_Death_From_Front);
		float DeltaTime = g_gameTime.GetFrameDeltaTime();
		m_animation.Update(DeltaTime);
		return;
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
	Vector3 moveVec = m_PassPos[NextPass] - m_pos;
	//���̃p�X�ւ̋��������ȓ��Ȃ�
	if (moveVec.Length() <= PassDist)
	{
		//�ړI�n�̒������̂�
		//���݂̃p�X��ύX
		CurrentPass = NextPass;
	}

	//���̃p�X�ւ̃x�N�g��
	moveVec.y = 0.0f;
	moveVec.Normalize();
	
	//���̃p�X�֌�������]
	m_rot.SetRotation(Vector3::AxisZ, moveVec);

	float DeltaTime = g_gameTime.GetFrameDeltaTime();
	Vector3 footStepValue = Vector3::Zero;

	static float i = 0;
	i += DeltaTime;
	if (i > 10.0f)
	{
		m_Status->Damage(100);
	}

	//�A�j���[�V��������footstep�̈ړ��ʂ������Ă���
	footStepValue = m_animation.Update(DeltaTime);

	//Max�Ƃ͎����Ⴄ�̂Ŏ������킹��
	float value = footStepValue.y;
	footStepValue.y = footStepValue.z;
	footStepValue.z = -value;
	//�t�b�g�X�e�b�v�𒲐�
	footStepValue *= footStepAdjustValue;
	
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
	currentState->Update();

	//footStep�ɉ�]��K��
	m_rot.Apply(footStepValue);

	//�L�����R���̌v�Z
	Vector3 returnPos = characon->Execute(footStepValue, DeltaTime);

	m_pos = returnPos;
	
	m_enemyModel->SetPosition(m_pos);
	m_enemyModel->SetRotation(m_rot);

	if (IsDead == true)
	{
		delete characon;
		characon = nullptr;
	}
}