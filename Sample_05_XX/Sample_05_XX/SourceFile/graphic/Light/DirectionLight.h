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
		///// �f�B���N�V�������C�g�B
		//struct DirectionalLight {
		//	Vector3 direction;	//���C�g�̕����B
		//	float pad0;			//�p�f�B���O�B
		//	Vector4 color;		//���C�g�̃J���[�B
		//};
	};
}