#include "stdafx.h"
#include "PlayerStateMove.h"
#include "Player.h"

PlayerStateMove::~PlayerStateMove()
{

}

void PlayerStateMove::Update()
{
	m_Player->PlayAnimation(1);
	//回転
	Quaternion q_rot = Quaternion::Identity;
	//プレイヤーの前方向
	Vector3 playerforward = Vector3::Zero;
	//移動方向
	Vector3 movedir = Vector3::Zero;
	
	//プレイヤーの前方向をゲット
	playerforward = m_Player->GetForward();
	//カメラの前方向をゲット
	movedir = g_camera3D->GetForward();
	movedir.y = 0.0f;
	movedir.Normalize();

	//キー入力による移動方向の計算
	//まずはカメラの移動方向を計算
	Vector3 KeyDir = movedir * g_pad[0]->GetLStickYF();
	//カメラの右方向をゲット
	Vector3 playerRight = Cross(Vector3::Up, movedir);
	//カメラの左右の移動方向を計算
	KeyDir += playerRight* g_pad[0]->GetLStickXF();
	KeyDir.Normalize();

	//プレイヤーの前方向からキー入力方向への回転を計算
	q_rot.SetRotation(playerforward, KeyDir);

	//プレイヤーに回転をセット
	m_Player->SetRotation(q_rot);
}
