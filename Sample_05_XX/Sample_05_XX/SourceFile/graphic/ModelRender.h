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
			const char* m_vsEntryPointFunc = "VSMain";	//���_�V�F�[�_�[�̃G���g���[�|�C���g�B
			const char* m_psEntryPointFunc = "PSDefferdMain";	//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g�B
			const char* m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";			//fx�t�@�C���̃t�@�C���p�X�B
			Light light;
			void* m_expandConstantBuffer = &light;		//���[�U�[�g���̒萔�o�b�t�@�B
			int m_expandConstantBufferSize = 0;			//���[�U�[�g���̒萔�o�b�t�@�̃T�C�Y�B
			IShaderResource* m_expandShaderResoruceView = nullptr;	//���[�U�[�g���̃V�F�[�_�[���\�[�X�B
			ModelInitData InitData;
			Skeleton m_skeleton;
		};
	}
}