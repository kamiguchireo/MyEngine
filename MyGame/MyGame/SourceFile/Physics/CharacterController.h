#pragma once
#include "CapsuleCollider.h"
#include "RigidBody.h"

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
			RemoveRigidBody();
		}

		//初期化
		//radius		カプセルコライダーの半径
		//height		カプセルコライダーの高さ
		//position		初期位置
		void Init(float radius, float height, const Vector3& position);

		//実行
		//moveSpeed		移動速度
		//deltaTime		経過時間。単位は秒。デフォルトでは1フレームの経過時間が渡されている
		//return		移動後のキャラクターの座標
		const Vector3& Execute(Vector3& moveSpeed);

		//剛体をフィジックスワールドから削除
		void RemoveRigidBody();

		RigidBody* GetRigidBody()
		{
			return &m_rigidBody;
		}

		//地面の上にいるかどうか
		bool IsOnGround()const
		{
			return m_isOnGround;
		}
	private:
		bool m_isInited = false;		//初期化フラグ
		Vector3 m_position = Vector3::Zero;		//座標
		bool m_isJump = false;		//ジャンプフラグ
		bool m_isOnGround = true;		//地面の上にいる
		CapsuleCollider m_collider;		//コライダー
		float m_radius = 0.0f;		//カプセルコライダーの半径
		float m_height = 0.0f;		//カプセルコライダーの高さ
		RigidBody m_rigidBody;		//剛体
		const float OverStep = 0.25f;
	};
}