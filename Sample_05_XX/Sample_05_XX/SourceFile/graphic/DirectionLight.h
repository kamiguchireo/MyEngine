#pragma once
namespace Engine {
	class DirectionLight :public IGameObject
	{
	public:
		DirectionLight();
		~DirectionLight();

		bool Start();
		void Update();
	};
}