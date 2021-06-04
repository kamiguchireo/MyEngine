#pragma once
#include "SourceFile/graphic/ModelRender.h"

namespace Engine {
	namespace prefab {
		class Sky : public IGameObject
		{
		public:
			Sky();
			~Sky();

			bool Start();

		private:
			ModelRender* m_skyModel = nullptr;
			Vector3 m_scale = { 1000.0f,1000.0f,1000.0f };
			Vector3 m_pos = Vector3::Zero;
		};
	}
}