#pragma once
#include "CapsuleCollider.h"

//キャラクターコントローラー
//キャラクターと背景の衝突解決を行う
namespace Engine {
	class CharacterController
	{
	public:
		CharacterController()
		{

		}
		~CharacterController()
		{

		}

		//初期化
		//radius		カプセルコライダーの半径
		//height		カプセルコライダーの高さ
		//position		初期位置
		void Init(float radius, float height, const Vector3& position);

	private:
		bool m_isInited = false;		//初期化フラグ
		Vector3 m_position = Vector3::Zero;		//座標
		bool m_isJump = false;		//ジャンプフラグ
		bool m_isOnGround = true;		//地面の上にいる
		CapsuleCollider m_collider;		//コライダー
		float m_radius = 0.0f;		//カプセルコライダーの半径
		float m_height = 0.0f;		//カプセルコライダーの高さ

	};
}