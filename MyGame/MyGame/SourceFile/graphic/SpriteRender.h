#pragma once
namespace Engine {
	namespace prefab {
		class SpriteRender:public IGameObject
		{
		public:
			SpriteRender();
			~SpriteRender();

		private:
			Sprite m_sprite;
			SpriteInitData m_SpriteInitData;
		};
	}
}