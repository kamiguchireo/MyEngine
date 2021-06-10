//�X�J�C�L���[�u�\���p�̃V�F�[�_�[

cbuffer ModelCb:register(b0)
{
	float4x4 mWorld:packoffset(c0);
	float4x4 mView:packoffset(c4);
	float4x4 mProj:packoffset(c8);
};

//�e�N�X�`��
TextureCube<float4> skyCubeMap : register(t0);
//�T���v���[�X�e�[�g
sampler g_sampler : register(s0);

//���_�V�F�[�_�[�ւ̓���
struct SVSIn {
	float4 pos : POSITION;		//�|�W�V����
	float3 normal	: NORMAL;		//�@���B
};

//�s�N�Z���V�F�[�_�[�ւ̏o��
struct SPSIn {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;		//�@���B
};
//���_�V�F�[�_�[
SPSIn VSMain(SVSIn vsIn)
{
	SPSIn psout = (SPSIn)0;
	psout.pos = mul(mWorld, vsIn.pos);
	psout.pos = mul(mView, psout.pos);
	psout.pos = mul(mProj, psout.pos);
	psout.normal = normalize(mul(mWorld, vsIn.normal));
	return psout;
}

//�s�N�Z���V�F�[�_�[
float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 color = skyCubeMap.Sample(g_sampler,psIn.normal);
	return color;
}