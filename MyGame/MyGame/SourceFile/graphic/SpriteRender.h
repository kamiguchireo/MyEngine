#pragma once
namespace Engine {
	namespace prefab {
		class SpriteRender:public IGameObject
		{
		public:
			SpriteRender();
			~SpriteRender();

			//更新関数
			//自動で呼ばれます
			void Update();

			//ポストレンダー
			//自動で呼ばれます
			void PostRender();

			//ファイルパスをセット
			//Filepath		ファイルパス
			void Init(const char* Filepath,int height,int width)
			{
				//ファイルパスをセット
				m_SpriteInitData.m_ddsFilePath[0] = Filepath;
				//高さを指定
				m_SpriteInitData.m_height = height;
				//幅を指定
				m_SpriteInitData.m_width = width;
				//スプライトを初期化
				m_sprite.Init(m_SpriteInitData);
				//初期化フラグを立てる
				IsInited = true;
			}

			//ポジションをセット
			//pos		位置
			void SetPosition(const Vector3& pos)
			{
				m_pos = pos;
			}

			//拡大率をセット
			void SetScale(const Vector3& scale)
			{
				m_scale = scale;
			}

			//回転をセット
			void SetRotation(const Quaternion& rot)
			{
				m_rot = rot;
			}

			//αの設定
			//f		αの値
			void SetAlpha(float f)
			{
				m_sprite.SetAlpha(f);
			}
		private:
			Sprite m_sprite;		//スプライト
			SpriteInitData m_SpriteInitData;		//初期化データ
			Vector3 m_pos = Vector3::Zero;		//位置
			Quaternion m_rot = Quaternion::Identity;		//回転
			Vector3 m_scale = Vector3::One;		//拡大率
			Vector2 m_pivot = { 0.5f,0.5f };		//起点
			bool IsInited = false;		//初期化フラグ
		};
	}
}