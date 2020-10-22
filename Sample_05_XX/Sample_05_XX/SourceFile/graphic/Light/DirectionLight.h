#pragma once
namespace Engine {
	class DirectionLight :public IGameObject
	{
	public:
		DirectionLight();
		~DirectionLight();

		bool Start();
		void Update();

	private:
		///// ディレクションライト。
		//struct DirectionalLight {
		//	Vector3 direction;	//ライトの方向。
		//	float pad0;			//パディング。
		//	Vector4 color;		//ライトのカラー。
		//};
	};
}