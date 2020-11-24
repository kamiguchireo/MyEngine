#pragma once

#include "tkFile/TkmFile.h"
#include "MeshParts.h"
#include "Skeleton.h"

class IShaderResource;

/// <summary>
/// モデルの初期化データ
/// </summary>
struct ModelInitData {
	const char* m_tkmFilePath = nullptr;		//tkmファイルパス。
	const char* m_vsEntryPointFunc = "VSMain";	//頂点シェーダーのエントリーポイント。
	const char* m_psEntryPointFunc = "PSMain";	//ピクセルシェーダーのエントリーポイント。
	const char* m_fxFilePath = nullptr;			//.fxファイルのファイルパス。
	IShaderResource* m_expandShaderResoruceView = nullptr;	//ユーザー拡張のシェーダーリソース。
};
/// <summary>
/// モデルクラス。
/// </summary>
class Model {

public:

	/// <summary>
	/// tkmファイルから初期化。
	/// </summary>
	/// <param name="initData">初期化データ</param>
	void Init(const ModelInitData& initData,int m_maxInstance = 0);
	/// <summary>
	/// ワールド行列の更新。
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale);

	/// <summary>
	/// スケルトンを関連付ける。
	/// </summary>
	/// <param name="skeleton">スケルトン</param>
	void BindSkeleton(Skeleton& skeleton)
	{
		m_meshParts.BindSkeleton(skeleton);
	}

	//レベルを関連付ける
	void BindLevelObject(std::vector<Matrix>& mat)
	{
		m_meshParts.BindLevelWardlMatrix(mat);
	}
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="renderContext">レンダリングコンテキスト</param>
	void Draw(RenderContext& renderContext);
	void Draw(RenderContext& renderContext,Matrix viewMat,Matrix proMat,int rendermode = 1);

	/// <summary>
	/// ワールド行列を取得。
	/// </summary>
	/// <returns></returns>
	const Matrix& GetWorldMatrix() const
	{
		return m_world;
	}

	void SetShadowRecieverFlag(bool flag)
	{
		IsShadowReciever = flag;
	}

private:

	Matrix m_world;			//ワールド行列。
	TkmFile m_tkmFile;		//tkmファイル。
	MeshParts m_meshParts;	//メッシュパーツ。
	bool IsShadowReciever = false;
	int m_numInstance = 0;
	int m_maxInstance = 1;
};