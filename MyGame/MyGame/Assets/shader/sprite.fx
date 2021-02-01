
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
	float t2 = t * t;
	float t4 = t * t * t * t;
	float m2 = m * m;
	float D = 1.0f / (4.0f * m2 * t4);
	D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
	return D;
}

float spcFresnel(float f0, float u)
{
	return f0 + (1 - f0) * pow(1 - u, 5);
}

//L		光源に向かうベクトル
//V		視線に向かうベクトル
//N		法線
float BRDF(float3 L, float3 V, float3 N, float metaric)
{
	float microfacet = 0.3f;
	float f0 = metaric;		//鏡面反射の度合い
	//光源に向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
	float3 H = normalize(L + V);

	float NdotH = max(0.01f, dot(N, H));
	float VdotH = max(0.01f, dot(V, H));
	float NdotL = max(0.01f, dot(N, L));
	float NdotV = max(0.01f, dot(N, V));

	float D = Beckmann(microfacet, NdotH);
	float F = spcFresnel(f0, VdotH);

	float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));
	float m = PI * NdotV * NdotL;

	return max(F * D * G / m, 0.0f);
}

//N		法線
//L		光源に向かうベクトル
//V		視線に向かうベクトル
//roughness		スペキュラ
float3 NormalizedDisneyDiffuse(float3 N, float3 L, float3 V, float roughness)
{
	//法線と光源に向かうベクトルがどれだけ似ているかを内積で求める
	float dotNL = saturate(dot(N, L));
	//法線と視線に向かうベクトルがどれだけ似ているかを内積で求める
	float dotNV = saturate(dot(N, V));

	return max(0.2f, (dotNL * dotNV) / PI);
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
	float4 finalColor = albedo;
	float4 shadow = shadowTexture.Sample(Sampler, In.uv);
	float3 worldPos = worldPosTexture.Sample(Sampler, In.uv);
	float metaric = g_specularMap.Sample(Sampler, In.uv).r;
	//float4 metaricorigin = g_specularMap.Sample(Sampler, In.uv);
	//float metaric = (metaricorigin.r + metaricorigin.g + metaricorigin.b + metaricorigin.a) / 4;
	//ランバート拡散反射
	float3 lig = 0;
	//ライトをあてる物体から視点に向かって伸びるベクトルを計算する。
	float3 eyeToPixel = eyePos - worldPos;
	eyeToPixel = normalize(eyeToPixel);

	for (int i = 0; i < NUM_DIRECTIONAL_LIGHT; i++) {
		if (shadow.x < 1.0f || i != 0) {
			float NdotL = saturate(dot(normal, -directionalLight[i].direction));	//ライトの逆方向と法線で内積を計算する。
			//if (NdotL < 0.0f) {	//内積の計算結果はマイナスになるので、if文で判定する。
			//	NdotL = 0.0f;
			//}
			//拡散反射光を求める

			float disneyDiffuse = NormalizedDisneyDiffuse(normal, -directionalLight[i].direction, eyeToPixel, 1.0f);
			float3 Diffuse = directionalLight[i].color * NdotL * disneyDiffuse / PI;
			//return float4(Diffuse, 1.0f);
			//スペキュラ反射を求める
			float3 Spec = BRDF(-directionalLight[i].direction, eyeToPixel, normal, metaric);
			Spec *= directionalLight[i].color;
			lig += lerp(Diffuse, Spec, metaric);
		}
	}
	//正規化ランバート拡散反射が起きていると考える。
	lig += ambinentLight / PI * (1.0f - metaric);
	//環境光による鏡面反射を計算する。
	//光が法線方向から入射していると考えて鏡面反射を計算する。
	lig += BRDF(normal, eyeToPixel, normal, metaric) * ambinentLight * metaric;


	finalColor.xyz *= lig;
	return finalColor;
}