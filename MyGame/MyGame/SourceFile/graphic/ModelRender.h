#pragma once
#include "SourceFile/GameObject/GameObjectManager.h"

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

			//�f�B�t�@�[�h�ȊO���g�p����ꍇ�̓R�����g�A�E�g���O���Ă�������
			//�܂��������ł�
			//void Draw();

			//tkm�̃t�@�C���p�X���Z�b�g
			void SetTkmFilePath(const char*filePath)
			{
				m_tkmFilePath = filePath;
			}
			//���_�V�F�[�_�[�̃G���g���[�|�C���g���Z�b�g
			void SetVSEntryPoint(const char* EntryPoint)
			{
				m_vsEntryPointFunc = EntryPoint;
			}
			//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���Z�b�g
			void SetPSEntryPoint(const char* EntryPoint)
			{
				m_psEntryPointFunc = EntryPoint;
			}
			//�V�F�[�_�[�̃t�@�C���p�X���Z�b�g
			void SetfxFilePath(const char* FilePath)
			{
				m_fxFilePath = FilePath;
			}
			//�X�P���g�����Z�b�g
			void SetSkeleton(Skeleton& SK)
			{
				m_skeleton = &SK;
			}
			//���x���ŕ`�悷��I�u�W�F�N�g�̃��[���h�s����Z�b�g
			void SetLevelMatrix(std::vector<Matrix>& mat)
			{
				m_level = &mat;
			}
			//�V���h�E�L���X�^�[�ɂ��邩�ǂ����̃t���O���Z�b�g
			void SetShadowCasterFlag(bool flag)
			{
				m_ShadowCasterFlag = flag;
			}
			//�V���h�E���V�[�o�[�ɂ��邩�ǂ����̃t���O���Z�b�g
			void SetShadowRecieverFlag(bool flag)
			{
				m_model->SetShadowRecieverFlag(flag);
			}
			//�f�B�U�����O�����邩�ǂ����̃t���O
			void SetDitherFlag(bool flag)
			{
				m_model->SetDitherFlag(flag);
			}
			//�ʒu���Z�b�g
			void SetPosition(const Vector3& pos)
			{
				m_pos = pos;
			}
			//��]���Z�b�g
			void SetRotation(const Quaternion& rot)
			{
				m_rot = rot;
			}
			//�g�嗦���Z�b�g
			void SetScale(const Vector3& scale)
			{
				m_scale = scale;
			}
			//�C���X�^���X�̐����Z�b�g
			void SetInstanceNum(int num)
			{
				m_numInstance = num;
			}
			//�C���X�^���V���O�`�悷��I�u�W�F�N�g�̃��[���h�s����A�b�v�f�[�g
			void UpdateInstancingData(const Vector3& trans, const Quaternion& rot, const Vector3& scale)
			{
				m_model->UpdateInstancingData(trans, rot, scale);
			}
			//UpdateInstancingData���Ăԃt���[���Ɉ��Ă�ł��������B
			void ModelInstanceRefresh()
			{
				m_model->Refresh();
			}
			//�C���X�^���V���O�`�悷�郂�f���̃X�g���N�`���[�o�b�t�@���A�b�v�f�[�g
			void UpdateInstancingSTB()
			{
				m_model->UpdateInstancingSTB();
			}
			//���[���h�s��𒼐ڃZ�b�g
			void SetWorldMatrix(const Matrix& WorldMat)
			{
				m_model->SetWorldMatrix(WorldMat);
			}
			//���[���h�s��������ŃA�b�v�f�[�g���邩�ǂ����̃t���O
			void SetUpdateFlag(bool flag)
			{
				UpdateFlag = flag;
			}
			//�X�L�����f�����擾
			const Model& GetModel()const
			{
				return *m_model;
			}

			void InitTkmFile(const char* tkmFilePath)
			{
				m_model->LoadTkm(tkmFilePath);
			}
			
			void SetIsDefferd(bool flag)
			{
				IsDefferd = flag;
			}

			std::vector<SMesh*>& GetMeshs()
			{
				return m_model->GetMeshs();
			}
		private:
			Model* m_model = nullptr;
			Vector3 m_pos = Vector3::Zero;
			Quaternion m_rot = Quaternion::Identity;
			Vector3 m_scale = Vector3::One;
			const char* m_tkmFilePath = nullptr;
			const char* m_vsEntryPointFunc = "VSMain";	//���_�V�F�[�_�[�̃G���g���[�|�C���g�B
			const char* m_psEntryPointFunc = "PSDefferdMain";	//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g�B
			const char* m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";			//fx�t�@�C���̃t�@�C���p�X�B
			IShaderResource* m_expandShaderResoruceView = nullptr;	//���[�U�[�g���̃V�F�[�_�[���\�[�X�B
			ModelInitData InitData;
			Skeleton* m_skeleton = nullptr;
			std::vector<Matrix>* m_level = nullptr;
			bool m_ShadowCasterFlag = true;
			int m_numInstance = 1;
			bool UpdateFlag = true;
			bool IsInited = false;
			bool IsDefferd = true;
		};
	}
}