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

		private:
			Model m_model;
			Vector3 m_pos = Vector3::Zero;
			Quaternion m_rot = Quaternion::Identity;
			Vector3 m_scale = Vector3::One;
			RenderContext RC;
			const char* m_tkmFilePath = nullptr;
			const char* m_vsEntryPointFunc = "VSMain";	//頂点シェーダーのエントリーポイント。
			const char* m_psEntryPointFunc = "PSDefferdMain";	//ピクセルシェーダーのエントリーポイント。
			const char* m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";			//fxファイルのファイルパス。
			Light light;
			void* m_expandConstantBuffer = &light;		//ユーザー拡張の定数バッファ。
			int m_expandConstantBufferSize = 0;			//ユーザー拡張の定数バッファのサイズ。
			IShaderResource* m_expandShaderResoruceView = nullptr;	//ユーザー拡張のシェーダーリソース。
			ModelInitData InitData;
			Skeleton m_skeleton;
		};
	}
}