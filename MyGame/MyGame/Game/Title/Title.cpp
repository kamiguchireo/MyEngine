#include "stdafx.h"
#include "Title.h"
#include "SourceFile/level/Level.h"
#include "Game/Stage/Tree/Tree1.h"
#include "Game/Stage/Tree/Tree2.h"
#include "Game/Stage/Grass/Grass_03.h"
#include "Game/Game.h"

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
	//サウンド
	if (m_FireSound != nullptr)
	{
		DeleteGO(m_FireSound);
		m_FireSound = nullptr;
	}
	//スプライト
	if (m_BulletTitleSprite != nullptr)
	{
		DeleteGO(m_BulletTitleSprite);
		m_BulletTitleSprite = nullptr;
	}
	if (m_TitleStartSprite != nullptr)
	{
		DeleteGO(m_TitleStartSprite);
		m_TitleStartSprite = nullptr;
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
		else if (wcscmp(objData.name, L"SM_Grass_03") == 0)
		{
			//草
			if (m_Glass == nullptr)
			{
				m_Glass = NewGO<Grass_03>(0);
				m_Glass->InitInstance(objData.position, objData.rotation, objData.scale);
			}
			else
			{
				m_Glass->AddInstance(objData.position, objData.rotation, objData.scale);
			}
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
	m_FireSound->Init(L"Assets/sound/Anti_materiel_rifle.wav");

	//弾痕のスプライト
	m_BulletTitleSprite = NewGO<prefab::SpriteRender>(0);
	m_BulletTitleSprite->Init("Assets/image/BulletTitle.dds",250, 250);
	m_BulletTitleSprite->SetPosition(Vector3::Zero);
	m_BulletTitleSprite->SetAlpha(0.0f);

	//左クリックを押してスタートすると書かれたスプライト
	m_TitleStartSprite = NewGO<prefab::SpriteRender>(0);
	m_TitleStartSprite->Init("Assets/image/TitleStart.dds", 250, 750);
	m_TitleStartSprite->SetPosition({ 0.0f,-250,0.0f });
	m_TitleStartSprite->SetAlpha(1.0f);

	m_CameraPos = { 200.0f,150.0f,200.0f };
	m_CameraTarget = { 0.0f,150.0f,0.0f };
	return true;
}

void Title::CameraMove()
{
	//補完後のカメラの設定
	Vector3 NextCameraPos = { 100.0f,25.0f,350 };
	Vector3 NextCameraTarget = { -100.0f,80.0f,0.0f };
	Vector3 NextCameraUp = { -0.5f,0.0f,-0.5f };

	//補完率
	static float interpolate = 0.0f;
	interpolate += g_gameTime.GetFrameDeltaTime() * 0.2f;
	//補完率を二乗する
	float f = pow(interpolate, 2.0);
	
	//最大値を1にする
	if (f >= 1.0f)
	{
		f = 1.0f;
		m_process = TitleProcess::enProcess_Fade;
	}

	m_CameraPos.Lerp(f, m_CameraPos, NextCameraPos);
	m_CameraTarget.Lerp(f, m_CameraTarget, NextCameraTarget);
	m_CameraUp.Lerp(f, m_CameraUp, NextCameraUp);
	g_camera3D->SetUp(m_CameraUp);
}

void Title::Update()
{
	auto deltatime = g_gameTime.GetFrameDeltaTime();
	if (m_process == TitleProcess::enProcess_Start)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_animation.Play(enTitleCharacterAnimation_Rifle_Down_To_Aim, 0.3f);
			m_process = TitleProcess::enProcess_Click;
		}
	}
	else if (m_process == TitleProcess::enProcess_Click)
	{
		if (m_animation.IsPlaying() == false)
		{
			m_FireSound->Play(false, false);
			m_BulletTitleSprite->SetAlpha(1.0f);
			m_process = TitleProcess::enProcess_PlaySound;
		}
	}
	else if (m_process == TitleProcess::enProcess_PlaySound)
	{
		CameraMove();
	}
	else if (m_process == TitleProcess::enProcess_Fade)
	{
		g_graphicsEngine->GetFade()->FadeOut();
		m_process = TitleProcess::enProcess_WithoutAlpha;
	}
	else if (m_process == TitleProcess::enProcess_WithoutAlpha)
	{
		float alpha = 1.0f - g_graphicsEngine->GetFade()->GetAlpha();
		if (alpha <= 0.001f)
		{
			//限りなく0に近いので0にする
			alpha = 0.0f;
			m_process = TitleProcess::enProcess_SceneTrans;
		}
		m_BulletTitleSprite->SetAlpha(alpha);
	}
	else if (m_process = TitleProcess::enProcess_SceneTrans)
	{
		auto g_game = Game::GetInstance();
		//ステージ01呼び出し
		g_game->SceneTrans(SceneNum::enScene_Stage01);
		return;
	}
	m_animation.Update(deltatime);

	g_camera3D->SetPosition(m_CameraPos);
	g_camera3D->SetTarget(m_CameraTarget);
	m_skinModel->SetPosition(m_pos);
	m_skinModel->SetRotation(m_rot);
}