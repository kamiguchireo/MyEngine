#pragma once

namespace Engine {
	namespace prefab{
		class ModelRender :public IGameObject
		{
		public:
			ModelRender();
			~ModelRender();

			bool Start();
			void Update();
			void Draw();

			//ディファード以外を使用する場合はコメントアウトを外してください
			//まだ未実装です
			//void Draw();

			void SetTkmFilePath(const char*filePath)
			{
				m_tkmFilePath = filePath;
			}
			void SetVSEntryPoint(const char* EntryPoint)
			{
				m_vsEntryPointFunc = EntryPoint;
			}
			void SetPSEntryPoint(const char* EntryPoint)
			{
				m_psEntryPointFunc = EntryPoint;
			}
			void SetfxFilePath(const char* FilePath)
			{
				m_fxFilePath = FilePath;
			}

			void SetSkeleton(Skeleton& SK)
			{
				m_skeleton = &SK;
			}

			void SetShadowCasterFlag(bool flag)
			{
				m_ShadowCasterFlag = flag;
			}

			void SetShadowRecieverFlag(bool flag)
			{
				m_model.SetShadowRecieverFlag(flag);
			}

			void SetPosition(Vector3 pos)
			{
				m_pos = pos;
			}

			void SetRotation(Quaternion rot)
			{
				m_rot = rot;
			}

			void SetScale(Vector3 scale)
			{
				m_scale = scale;
			}
		private:
			Model m_model;
			Vector3 m_pos = Vector3::Zero;
			Quaternion m_rot = Quaternion::Identity;
			Vector3 m_scale = Vector3::One;
			//RenderContext RC;
			const char* m_tkmFilePath = nullptr;
			const char* m_vsEntryPointFunc = "VSMain";	//頂点シェーダーのエントリーポイント。
			const char* m_psEntryPointFunc = "PSDefferdMain";	//ピクセルシェーダーのエントリーポイント。
			const char* m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";			//fxファイルのファイルパス。
			IShaderResource* m_expandShaderResoruceView = nullptr;	//ユーザー拡張のシェーダーリソース。
			ModelInitData InitData;
			Skeleton* m_skeleton = nullptr;
			bool m_ShadowCasterFlag = true;
		};
	}
}