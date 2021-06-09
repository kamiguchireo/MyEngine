//スカイキューブ表示用のシェーダー

cbuffer ModelCb:register(b0)
{
	float4x4 mWorld:packoffset(c0);
	float4x4 mView:packoffset(c4);
	float4x4 mProj:packoffset(c8);
};

//テクスチャ
TextureCube<float4> skyCubeMap : register(t0);
//サンプラーステート
sampler g_sampler : register(s0);

//頂点シェーダーへの入力
struct SVSIn {
	float3 normal	: NORMAL;		//法線。
};

//ピクセルシェーダーへの出力
struct SPSIn {
	float3 normal : NORMAL;		//法線。
};
//頂点シェーダー
SPSIn VSMain(SVSIn vsIn)
{
	SPSIn psout = (SPSIn)0;
	psout.normal = normalize(mul(mWorld, vsIn.normal));
	return psout;
}

//ピクセルシェーダー
float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 color = skyCubeMap.Sample(g_sampler,psIn.normal);
	return color;
}