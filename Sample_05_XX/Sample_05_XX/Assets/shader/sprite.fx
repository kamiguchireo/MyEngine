
static const int NUM_DIRECTIONAL_LIGHT = 4;	//ディレクションライトの本数。
static const float PI = 3.14159265358979323846;

cbuffer cb : register(b0){
	float4x4 mvp;
	float4 mulColor;
};

//ディレクションライト。
struct DirectionalLight {
	float3 direction;	//ライトの方向。
	float4 color;		//ライトの色。
};
//ライト用の定数バッファ。
cbuffer LightCb : register(b1) {
	DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];
	float3 eyePos;					//カメラの視点。
	float specPow;					//スペキュラの絞り。
	float3 ambinentLight;			//環境光。
};

struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//アルベド
Texture2D<float4> normalTexture : register(t1);	//法線。
Texture2D<float4> shadowTexture : register(t2);	//シャドウ用
Texture2D<float4> worldPosTexture : register(t3); //ワールド座標
Texture2D<float4> g_specularMap : register(t4); //スペキュラマップ

sampler Sampler : register(s0);

float Beckmann(float m, float t)
{
	float M = m * m;
	float T = t * t;
	return exp((T - 1) / (M * T)) / (M * T * T);
}

float spcFresnel(float f0, float u)
{
	return f0 + (1 - f0) * pow(1 - u, 5.0f);
}

//L		光源に向かうベクトル
//V		視線に向かうベクトル
//N		法線
float BRDF(float3 L, float3 V, float3 N)
{
	float microfacet = 0.3f;
	float f0 = 0.5f;
	bool include_F = 0;
	bool include_G = 0;
	//光源に向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
	float3 H = normalize(L + V);

	float NdotH = dot(N, H);
	float VdotH = dot(V, H);
	float NdotL = dot(N, L);
	float NdotV = dot(N, V);

	float D = Beckmann(microfacet, NdotH);
	float F = spcFresnel(f0, VdotH);

	float t = 2.0f * NdotH / VdotH;
	float G = max(0.0f, min(1.0f, min(t * NdotV, t * NdotL)));
	float m = 3.14159265 * NdotV * NdotL;

	return max(F * D * G / m, 0.0f);
}

float SchlickFresnel(float u, float f0, float f90)
{
	return f0 + (f90 - f0) * pow(1.0f - u, 5.0f);
}
//N		法線
//L		光源に向かうベクトル
//V		視線に向かうベクトル
//roughness		スペキュラ
float3 NormalizedDisneyDiffuse(float3 N, float3 L, float3 V, float roughness)
{
	//光源に向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
	float3 H = normalize(L + V);

	float energyBias = lerp(0.0f, 0.5f, roughness);
	float energyFactor = lerp(1.0f, 1.0f / 1.51f, roughness);
	//光源に向かうベクトルとハーフベクトルがどれだけ似ているかを内積で求める
	float dotLH = saturate(dot(L, H));
	//法線と光源に向かうベクトルがどれだけ似ているかを内積で求める
	float dotNL = saturate(dot(N, L));
	//法線と視線に向かうベクトルがどれだけ似ているかを内積で求める
	float dotNV = saturate(dot(N, V));

	float Fd90 = energyBias + 2.0 * dotLH * dotLH * roughness;

	float FL = SchlickFresnel(1.0f, Fd90, dotNL);
	float FV = SchlickFresnel(1.0f, Fd90, dotNV);

	return (FL * FV) / PI;
}

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
	return colorTexture.Sample(Sampler, In.uv) * mulColor;
}

float4 PSDefferd(PSInput In) : SV_Target0
{
	float4 albedo = colorTexture.Sample(Sampler,In.uv);
	float3 normal = normalTexture.Sample(Sampler, In.uv);
	normal = (normal * 2.0f) - 1.0f;
	float4 finalColor = albedo;
	float4 shadow = shadowTexture.Sample(Sampler, In.uv);
	float3 worldPos = worldPosTexture.Sample(Sampler, In.uv);
	float metaric = g_specularMap.Sample(Sampler, In.uv).a;

	float3 lig = 0;

	for (int i = 0; i < NUM_DIRECTIONAL_LIGHT; i++) {
		float NdotL = dot(normal, -directionalLight[i].direction);	//ライトの逆方向と法線で内積を計算する。
		if (NdotL < 0.0f) {	//内積の計算結果はマイナスになるので、if文で判定する。
			NdotL = 0.0f;
		}
		//ライトをあてる物体から視点に向かって伸びるベクトルを計算する。
		float3 eyeToPixel = eyePos - worldPos;
		eyeToPixel = normalize(eyeToPixel);

		//拡散反射光を求める
		float3 Diffuse = NormalizedDisneyDiffuse(normal, directionalLight[i].direction, eyeToPixel, 1.0f - metaric);
		Diffuse *= directionalLight[i].color * (1.0f - metaric) * NdotL;

		//スペキュラ反射を求める
		float3 Spec = BRDF(-directionalLight[i].direction, eyeToPixel, normal);
		Spec *= directionalLight[i].color * metaric;
		//スペキュラ反射の光を足し算する。
		lig += (Diffuse + Spec);
	}

	lig += ambinentLight;
	if (shadow.x == 1.0f)
	{
		lig *= 0.5f;
	}
	finalColor.xyz *= lig;
	return finalColor;
}