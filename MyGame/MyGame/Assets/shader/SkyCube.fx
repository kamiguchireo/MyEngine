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
	float4 pos : POSITION;		//ポジション
	float3 normal	: NORMAL;		//法線。
};

//ピクセルシェーダーへの出力
struct SPSIn {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;		//法線。
};
//頂点シェーダー
SPSIn VSMain(SVSIn vsIn)
{
	SPSIn psout = (SPSIn)0;
	psout.pos = mul(mWorld, vsIn.pos);
	psout.pos = mul(mView, psout.pos);
	psout.pos = mul(mProj, psout.pos);
	psout.normal = normalize(mul(mWorld, vsIn.normal));
	return psout;
}

//ピクセルシェーダー
float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 color = skyCubeMap.Sample(g_sampler,psIn.normal);
	return color;
}