#include "stdafx.h"
#include "Title.h"
#include "SourceFile/level/Level.h"
#include "Game/Stage/Tree/Tree1.h"
#include "Game/Stage/Tree/Tree2.h"

Title::~Title()
{

}

void Title::OnDestroy()
{
	//レベルを削除
	if (m_level != nullptr)
	{
		delete m_level;
		m_level = nullptr;
	}
	//スキンモデルを削除
	if (m_skinModel != nullptr)
	{
		DeleteGO(m_skinModel);
		m_skinModel = nullptr;
	}
	//武器を削除
	if (m_weapon != nullptr)
	{
		DeleteGO(m_weapon);
		m_weapon = nullptr;
	}
	//木を削除
	if (m_Tree1 != nullptr)
	{
		DeleteGO(m_Tree1);
		m_Tree1 = nullptr;
	}
	if (m_Tree2 != nullptr)
	{
		DeleteGO(m_Tree2);
		m_Tree2 = nullptr;
	}
	if (m_FireSound != nullptr)
	{
		DeleteGO(m_FireSound);
		m_FireSound = nullptr;
	}
}

bool Title::Start()
{
	if (m_level == nullptr)
	{
		m_level = new Level();
	}

	m_level->Init("Assets/Level/Title.tkl", [&](const LevelObjectData& objData) {
		if (wcscmp(objData.name, L"Soldier_bs01") == 0)
		{
			m_pos = objData.position;
			m_rot = objData.rotation;
			m_skinModel = NewGO<prefab::ModelRender>(0);
			//Tkmファイルをセット
			m_skinModel->SetTkmFilePath("Assets/modelData/soldier_bs01.tkm");
			//頂点シェーダーのエントリーポイント
			m_skinModel->SetVSEntryPoint("VSMainSkin");
			//スケルトンをセット
			m_skinModel->SetSkeleton(m_skeleton);
			//スケルトンとアニメーションの初期化
			m_skeleton.Init("Assets/modelData/soldier_bs01.tks");
			//スケルトンのアップデート
			m_skeleton.Update(Matrix::Identity);
			//武器をNewGO
			m_weapon = NewGO<Weapon>(1);
			m_weapon->Init(&m_skeleton, false);
			//位置をセット
			m_skinModel->SetPosition(m_pos);
			//回転をセット
			m_skinModel->SetRotation(m_rot);
			//アニメーションをセット
			m_animClip[enTitleCharacterAnimation_Rifle_Idle].Load("Assets/animData/Rifle_Idle.tka");
			m_animClip[enTitleCharacterAnimation_Rifle_Idle].SetLoopFlag(false);
			m_animClip[enTitleCharacterAnimation_Rifle_Down_To_Aim].Load("Assets/animData/Rifle_Down_To_Aim.tka");
			m_animClip[enTitleCharacterAnimation_Rifle_Down_To_Aim].SetLoopFlag(false);

			//アニメーションを初期化
			m_animation.Init(m_skeleton, m_animClip, enTitleCharacterAnimation_Num);
			m_animation.Play(enTitleCharacterAnimation_Rifle_Idle);

			return true;
		}
		else if (wcscmp(objData.name, L"SM_Tree_Tropic_02_novines") == 0)
		{
			//木
			if (m_Tree1 == nullptr)
			{
				m_Tree1 = NewGO<Tree1>(0);
				m_Tree1->InitInstance(objData.position, objData.rotation, objData.scale);
			}
			else
			{
				m_Tree1->AddInstance(objData.position, objData.rotation, objData.scale);
			}
			return true;
		}
		else if (wcscmp(objData.name, L"SM_Tree_Tropic_02") == 0)
		{
			//木
			if (m_Tree2 == nullptr)
			{
				m_Tree2 = NewGO<Tree2>(0);
				m_Tree2->InitInstance(objData.position, objData.rotation, objData.scale);
			}
			else
			{
				m_Tree2->AddInstance(objData.position, objData.rotation, objData.scale);
			}
			return true;
		}
		return false;
	});


	m_FireSound = NewGO<SoundSource>(0);
	m_FireSound->Init(L"Assets/sound/Rifle_fire.wav");

	m_CameraPos = { 200.0f,150.0f,200.0f };
	m_CameraTarget = { 0.0f,150.0f,0.0f };
	return true;
}

void Title::Update()
{
	auto deltatime = g_gameTime.GetFrameDeltaTime();
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_animation.Play(enTitleCharacterAnimation_Rifle_Down_To_Aim, 0.3f);
		IsEnterGame = true;
	}
	if (IsEnterGame)
	{
		if (m_animation.IsPlaying() == false)
		{
			if (IsPlayFireSound == false)
			{
				m_FireSound->Play(false, false);
				IsPlayFireSound = true;
			}
			else
			{

			}
		}
	}

	m_animation.Update(deltatime);

	g_camera3D->SetPosition(m_CameraPos);
	g_camera3D->SetTarget(m_CameraTarget);
	m_skinModel->SetPosition(m_pos);
	m_skinModel->SetRotation(m_rot);
}