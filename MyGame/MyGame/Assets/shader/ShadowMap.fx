


//モデル用の定数バッファ
cbuffer ModelCb : register(b0) {
	float4x4 mWorld: packoffset(c0);
	float4x4 mView: packoffset(c4);
	float4x4 mProj: packoffset(c8);
};

//モデルテクスチャ
Texture2D<float4> g_texture : register(t0);
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t3);
//インスタンシング描画用
StructuredBuffer<float4x4> instanceMatrix : register(t7);

//サンプラステート。
sampler g_sampler : register(s0);

//頂点シェーダーへの入力。
struct SVSIn {
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;		//法線。
	float2 uv 		: TEXCOORD0;	//UV座標。
	float3 tangent	: TANGENT;			//接ベクトル
	float3 biNormal : BINORMAL;
};
//スキンありモデルの頂点シェーダーへの入力
struct SVSInSkin {
	float4 pos		: POSITION;			//モデルの頂点座標
	float3 normal	: NORMAL;			//法線
	float2 uv		: TEXCOORD0;		//UV座標
	float3 tangent	: TANGENT;			//接ベクトル
	uint4 Indices	: BLENDINDICES0;	//この頂点に関連付けされているボーン番号
	float4 Weights	: BLENDWEIGHT0;		//この頂点に関連付けされているボーンウェイト
	float4 biNormal : BINORMAL;
};

//シャドウマップ用のピクセルシェーダーへの入力構造体
struct PSInput_ShadowMap {
	float4 Position:SV_POSITION;		//座標
	float2 uv 		: TEXCOORD0;	//UV座標。
};

PSInput_ShadowMap VSMain_ShadowMapCore(SVSIn In, float4x4 worldMat)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;

	float4 pos = mul(worldMat, In.pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	float4 texColor = g_texture.Sample(g_sampler, In.uv);
	psInput.uv = In.uv;
	return psInput;
}

//シャドウマップ生成用のスキンなしモデル頂点シェーダー
PSInput_ShadowMap VSMain_ShadowMap(SVSIn In)
{
	return VSMain_ShadowMapCore(In, mWorld);
}
//シャドウマップ生成用インスタンシングのスキンなしモデル頂点シェーダー
PSInput_ShadowMap VSMain_ShadowMapInstancing(SVSIn In, uint instanceID : SV_InstanceID)
{
	return VSMain_ShadowMapCore(In, instanceMatrix[instanceID]);
}


//シャドウマップ生成用のスキンモデル頂点シェーダー
PSInput_ShadowMap VSMain_ShadowMapSkin(SVSInSkin In)
{
	//初期化
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//最後のボーンを計算する。
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
		pos = mul(skinning, In.pos);
	}

	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.uv = In.uv;

	return psInput;
}

//ピクセルシェーダーのエントリ関数
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//テクスチャのαを参照して透過ならピクセルキル
	float4 texColor = g_texture.Sample(g_sampler, In.uv);
	clip(texColor.a - 1.0f);

	//射影空間でのZ値を返す
	return In.Position.z / In.Position.w;
}