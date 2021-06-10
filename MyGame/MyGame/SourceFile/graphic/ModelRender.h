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

			//ディファード以外を使用する場合はコメントアウトを外してください
			//まだ未実装です
			//void Draw();

			//tkmのファイルパスをセット
			void SetTkmFilePath(const char*filePath)
			{
				m_tkmFilePath = filePath;
			}
			//頂点シェーダーのエントリーポイントをセット
			void SetVSEntryPoint(const char* EntryPoint)
			{
				m_vsEntryPointFunc = EntryPoint;
			}
			//ピクセルシェーダーのエントリーポイントをセット
			void SetPSEntryPoint(const char* EntryPoint)
			{
				m_psEntryPointFunc = EntryPoint;
			}
			//シェーダーのファイルパスをセット
			void SetfxFilePath(const char* FilePath)
			{
				m_fxFilePath = FilePath;
			}
			//スケルトンをセット
			void SetSkeleton(Skeleton& SK)
			{
				m_skeleton = &SK;
			}
			//レベルで描画するオブジェクトのワールド行列をセット
			void SetLevelMatrix(std::vector<Matrix>& mat)
			{
				m_level = &mat;
			}
			//シャドウキャスターにするかどうかのフラグをセット
			void SetShadowCasterFlag(bool flag)
			{
				m_ShadowCasterFlag = flag;
			}
			//シャドウレシーバーにするかどうかのフラグをセット
			void SetShadowRecieverFlag(bool flag)
			{
				m_model->SetShadowRecieverFlag(flag);
			}
			//ディザリングをするかどうかのフラグ
			void SetDitherFlag(bool flag)
			{
				m_model->SetDitherFlag(flag);
			}
			//位置をセット
			void SetPosition(const Vector3& pos)
			{
				m_pos = pos;
			}
			//回転をセット
			void SetRotation(const Quaternion& rot)
			{
				m_rot = rot;
			}
			//拡大率をセット
			void SetScale(const Vector3& scale)
			{
				m_scale = scale;
			}
			//インスタンスの数をセット
			void SetInstanceNum(int num)
			{
				m_numInstance = num;
			}
			//インスタンシング描画するオブジェクトのワールド行列をアップデート
			void UpdateInstancingData(const Vector3& trans, const Quaternion& rot, const Vector3& scale)
			{
				m_model->UpdateInstancingData(trans, rot, scale);
			}
			//UpdateInstancingDataを呼ぶフレームに一回呼んでください。
			void ModelInstanceRefresh()
			{
				m_model->Refresh();
			}
			//インスタンシング描画するモデルのストラクチャーバッファをアップデート
			void UpdateInstancingSTB()
			{
				m_model->UpdateInstancingSTB();
			}
			//ワールド行列を直接セット
			void SetWorldMatrix(const Matrix& WorldMat)
			{
				m_model->SetWorldMatrix(WorldMat);
			}
			//ワールド行列を自動でアップデートするかどうかのフラグ
			void SetUpdateFlag(bool flag)
			{
				UpdateFlag = flag;
			}
			//スキンモデルを取得
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
			const char* m_vsEntryPointFunc = "VSMain";	//頂点シェーダーのエントリーポイント。
			const char* m_psEntryPointFunc = "PSDefferdMain";	//ピクセルシェーダーのエントリーポイント。
			const char* m_fxFilePath = "Assets/shader/NoAnimModel_LambertSpecularAmbient.fx";			//fxファイルのファイルパス。
			IShaderResource* m_expandShaderResoruceView = nullptr;	//ユーザー拡張のシェーダーリソース。
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