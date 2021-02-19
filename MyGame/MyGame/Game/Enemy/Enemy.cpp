#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	m_pass = Pass::GetInstance();
}

Enemy::~Enemy()
{

	if (m_enemyModel != nullptr)
	{
		DeleteGO(m_enemyModel);
		m_enemyModel = nullptr;
	}
	if (m_camera != nullptr)
	{
		DeleteGO(m_camera);
		m_camera = nullptr;
	}
	if (m_pass != nullptr)
	{
		delete m_pass;
		m_pass = nullptr;
	}
}

bool Enemy::Start()
{
	m_camera = NewGO<GameCamera>(0, nullptr);

	characon.Init(10.0f, 50.0f, m_pos);

	//�ҋ@��Ԃ̃A�j���[�V����
	m_animClip[0].Load("Assets/animData/Rifle_Idle.tka");
	m_animClip[0].SetLoopFlag(true);
	//������Ԃ̃A�j���[�V����
	m_animClip[1].Load("Assets/animData/Rifle_Walk.tka");
	m_animClip[1].SetLoopFlag(true);
	//�����Ԃ̃A�j���[�V����
	m_animClip[2].Load("Assets/animData/Rifle_Run.tka");
	m_animClip[2].SetLoopFlag(true);
	//�X�v�����g��Ԃ̃A�j���[�V����
	m_animClip[3].Load("Assets/animData/Rifle_Sprint.tka");
	m_animClip[3].SetLoopFlag(true);
	//�G�C����Ԃ̃A�j���[�V����
	m_animClip[4].Load("Assets/animData/Rifle_Down_To_Aim.tka");
	m_animClip[4].SetLoopFlag(false);


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
	m_animation.Init(m_skeleton, m_animClip, 5);
	m_animation.Play(1);
	m_rot.SetRotationDegY(180.0f);
	return true;
}

void Enemy::Update()
{
	float DeltaTime = g_gameTime.GetFrameDeltaTime();
	Vector3 footStepValue = Vector3::Zero;
	//�A�j���[�V��������footstep�̈ړ��ʂ������Ă���
	footStepValue = m_animation.Update(DeltaTime);
	//Max�Ƃ͎����Ⴄ�̂Ŏ������킹��
	float value = footStepValue.y;
	footStepValue.y = footStepValue.z;
	footStepValue.z = -value;
	footStepValue.y = -1.0f;
	footStepValue *= 24;

	m_rot.Apply(footStepValue);

	Vector3 returnPos = characon.Execute(footStepValue, DeltaTime);
	Vector3 move_vec = returnPos - m_pos;
	if (move_vec.Length() < 0.01f)
	{
		m_rot.SetRotationDegY(rot);
		rot += 180.0f;
		if (rot >= 360)
		{
			rot = 0.0f;
		}
	}
	m_pos = returnPos;

	m_camera->SetTarget(m_pos);

	m_enemyModel->SetPosition(m_pos);
	m_enemyModel->SetRotation(m_rot);

}