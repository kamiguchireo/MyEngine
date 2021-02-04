#pragma once

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
	};
}