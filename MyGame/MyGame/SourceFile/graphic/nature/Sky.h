#pragma once
#include "SourceFile/graphic/ModelRender.h"

namespace Engine {
	class Sky
	{
	public:
		Sky();
		~Sky();

		bool Init();
		void Update();

	private:
		prefab::ModelRender* m_skyModel = nullptr;
		Vector3 m_scale = { 50.0f,50.0f,50.0f };
		Vector3 m_pos = Vector3::Zero;
		std::unique_ptr<Texture> m_tex = nullptr;
	};
}