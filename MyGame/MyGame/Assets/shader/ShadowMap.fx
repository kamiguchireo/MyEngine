


//���f���p�̒萔�o�b�t�@
cbuffer ModelCb : register(b0) {
	float4x4 mWorld: packoffset(c0);
	float4x4 mView: packoffset(c4);
	float4x4 mProj: packoffset(c8);
};

//���f���e�N�X�`��
Texture2D<float4> g_texture : register(t0);
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t3);
//�C���X�^���V���O�`��p
StructuredBuffer<float4x4> instanceMatrix : register(t7);

//�T���v���X�e�[�g�B
sampler g_sampler : register(s0);

//���_�V�F�[�_�[�ւ̓��́B
struct SVSIn {
	float4 pos 		: POSITION;		//���f���̒��_���W�B
	float3 normal	: NORMAL;		//�@���B
	float2 uv 		: TEXCOORD0;	//UV���W�B
	float3 tangent	: TANGENT;			//�ڃx�N�g��
	float3 biNormal : BINORMAL;
};
//�X�L�����胂�f���̒��_�V�F�[�_�[�ւ̓���
struct SVSInSkin {
	float4 pos		: POSITION;			//���f���̒��_���W
	float3 normal	: NORMAL;			//�@��
	float2 uv		: TEXCOORD0;		//UV���W
	float3 tangent	: TANGENT;			//�ڃx�N�g��
	uint4 Indices	: BLENDINDICES0;	//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ�
	float4 Weights	: BLENDWEIGHT0;		//���̒��_�Ɋ֘A�t������Ă���{�[���E�F�C�g
	float4 biNormal : BINORMAL;
};

//�V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�[�ւ̓��͍\����
struct PSInput_ShadowMap {
	float4 Position:SV_POSITION;		//���W
	float2 uv 		: TEXCOORD0;	//UV���W�B
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

//�V���h�E�}�b�v�����p�̃X�L���Ȃ����f�����_�V�F�[�_�[
PSInput_ShadowMap VSMain_ShadowMap(SVSIn In)
{
	return VSMain_ShadowMapCore(In, mWorld);
}
//�V���h�E�}�b�v�����p�C���X�^���V���O�̃X�L���Ȃ����f�����_�V�F�[�_�[
PSInput_ShadowMap VSMain_ShadowMapInstancing(SVSIn In, uint instanceID : SV_InstanceID)
{
	return VSMain_ShadowMapCore(In, instanceMatrix[instanceID]);
}


//�V���h�E�}�b�v�����p�̃X�L�����f�����_�V�F�[�_�[
PSInput_ShadowMap VSMain_ShadowMapSkin(SVSInSkin In)
{
	//������
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//�Ō�̃{�[�����v�Z����B
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
		pos = mul(skinning, In.pos);
	}

	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.uv = In.uv;

	return psInput;
}

//�s�N�Z���V�F�[�_�[�̃G���g���֐�
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�e�N�X�`���̃����Q�Ƃ��ē��߂Ȃ�s�N�Z���L��
	float4 texColor = g_texture.Sample(g_sampler, In.uv);
	clip(texColor.a - 1.0f);

	//�ˉe��Ԃł�Z�l��Ԃ�
	return In.Position.z / In.Position.w;
}