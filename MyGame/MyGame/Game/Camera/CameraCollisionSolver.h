#pragma once
#include "SourceFile/Physics/SphereCollider.h"

//カメラのコリジョン解決
//カメラを背景にめり込ませたくない場合に使ってください
namespace Engine {
	class CameraCollisionSolver
	{
	public:
		//コンストラクタ
		CameraCollisionSolver();
		//デストラクタ
		~CameraCollisionSolver();

		//初期化
		//radius		スフィアコライダーの半径
		void Init(float radius);

		//コリジョンの解決の実行
		//result		コリジョン解決を行った視点の座標
		//position		コリジョン解決を行う前の視点の座標
		//target		カメラの注視点
		//戻り値はコリジョン解決を行った場合はtrueが返ってくる
		bool Execute(Vector3& result, const Vector3& position, const Vector3& target);
	private:
		SphereCollider m_collider;		//コライダー
		float m_radius = 0.0f;		//半径
		bool m_isInited = false;		//初期化済みのフラグ
	};
}