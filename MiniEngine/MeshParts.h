/// <summary>
/// メッシュパーツクラス。
/// </summary>

#pragma once

#include "tkFile/TkmFile.h"
#include "StructuredBuffer.h"
#include "SourceFile/graphic/Light/SLight.h"

class RenderContext;
class Skeleton;
class Material;
class IShaderResource;

/// <summary>
/// メッシュ
/// </summary>
struct SMesh {
	VertexBuffer m_vertexBuffer;						//頂点バッファ。
	std::vector< IndexBuffer* >		m_indexBufferArray;	//インデックスバッファ。
	std::vector< Material* >		m_materials;			//マテリアル。
	std::vector<int>				skinFlags;				//スキンを持っているかどうかのフラグ。
};



/// <summary>
/// メッシュパーツ。
/// </summary>
class MeshParts {
public:
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~MeshParts();
	/// <summary>
	/// tkmファイルから初期化
	/// </summary>
	/// <param name="tkmFile">tkmファイル。</param>
	/// /// <param name="fxFilePath">fxファイルのファイルパス</param>
	/// <param name="vsEntryPointFunc">頂点シェーダーのエントリーポイントの関数名</param>
	/// <param name="psEntryPointFunc">ピクセルシェーダーのエントリーポイントの関数名</param>
	void InitFromTkmFile(
		const TkmFile& tkmFile,
		const wchar_t* fxFilePath,
		const char* vsEntryPointFunc,
		const char* psEntryPointFunc,
		//Engine::Light* expandData,
		//int expandDataSize,
		IShaderResource* expandShaderResourceView,
		StructuredBuffer* InstancinMat = nullptr,
		int maxInstance = 1
	) ;
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="rc">レンダリングコンテキスト</param>
	/// <param name="mWorld">ワールド行列</param>
	/// <param name="mView">ビュー行列</param>
	/// <param name="mProj">プロジェクション行列</param>
	/// <param name="light">ライト</param>
	void Draw(RenderContext& rc, const Matrix& mWorld, const Matrix& mView, const Matrix& mProj, int rendermode = 1, int IsShadowResieverFlag = 0,int IsDitherFlag = 0,int DitherDist = 250);
	/// <summary>
	/// スケルトンを関連付ける。
	/// </summary>
	/// <param name="skeleton">スケルトン</param>
	void BindSkeleton(Skeleton& skeleton) ;

	std::vector<SMesh*>& GetMeshs()
	{
		return m_meshs;
	}
private:
	/// <summary>
	/// tkmメッシュからメッシュを作成。
	/// </summary>
	/// <param name="mesh">メッシュ</param>
	/// <param name="meshNo">メッシュ番号</param>
	/// <param name="fxFilePath">fxファイルのファイルパス</param>
	/// <param name="vsEntryPointFunc">頂点シェーダーのエントリーポイントの関数名</param>
	/// <param name="psEntryPointFunc">ピクセルシェーダーのエントリーポイントの関数名</param>
	void CreateMeshFromTkmMesh(
		const TkmFile::SMesh& mesh, 
		int meshNo,
		const wchar_t* fxFilePath,
		const char* vsEntryPointFunc,
		const char* psEntryPointFunc );

	/// <summary>
	/// ディスクリプタヒープを作成。
	/// </summary>
	void CreateDescriptorHeaps();

//public:
//	//シェーダーのエントリーポイントのセット
//	//vsEntryPoint		頂点シェーダーのエントリーポイント
//	//psEntryPoint		ピクセルシェーダーのエントリーポイント
//	void SetShaders(const char* vsEntryPoint, const char* psEntryPoint);

private:
	//拡張SRVが設定されるレジスタの開始番号。
	const int EXPAND_SRV_REG__START_NO = 10;
	/// <summary>
	/// 定数バッファ。
	/// </summary>
	/// <remarks>
	/// この構造体を変更したら、SimpleModel.fxのCBも変更するように。
	/// </remarks>
	struct SConstantBuffer {
		Matrix mWorld;		//ワールド行列。
		Matrix mView;		//ビュー行列。
		Matrix mProj;		//プロジェクション行列。
		int IsShadowReciever;		//シャドウレシーバーにするかどうかのフラグ
		int IsDither;		//ディザリングするかどうかのフラグ
		int DitherDist;		//ディザリングの計算のためのカメラとモデルの距離
	};
	ConstantBuffer m_commonConstantBuffer;					//メッシュ共通の定数バッファ。
	IShaderResource* m_expandShaderResourceView = nullptr;	//ユーザー拡張シェーダーリソースビュー。
	StructuredBuffer m_boneMatricesStructureBuffer;			//ボーン行列の構造化バッファ。
	StructuredBuffer* m_instancingMatricesStructureBuffer = nullptr;
	std::vector< SMesh* > m_meshs;							//メッシュ。
	std::vector< DescriptorHeap > m_descriptorHeap;			//ディスクリプタヒープ。
	Skeleton* m_skeleton = nullptr;							//スケルトン。
	bool m_isCreateDescriptorHeap = false;					//ディスクリプタヒープを作成済み？
	int m_instanceNum = 1;		//インスタンスの数
};