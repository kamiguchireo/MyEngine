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
		Vector3 m_scale = { 1000.0f,1000.0f,1000.0f };
		Vector3 m_pos = Vector3::Zero;
	};
}