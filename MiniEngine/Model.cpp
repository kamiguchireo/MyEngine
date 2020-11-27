#include "stdafx.h"
#include "Model.h"


void Model::Init(const ModelInitData& initData,int maxInstance)
{

	//�����̃V�F�[�_�[�����[�h���鏈�������߂Ă���̂�
	//wchar_t�^�̕�����Ȃ̂ŁA�����ŕϊ����Ă����B
	wchar_t wfxFilePath[256];
	if (initData.m_fxFilePath == nullptr) {
		MessageBoxA(nullptr, "fx�t�@�C���p�X���w�肳��Ă��܂���B", "�G���[", MB_OK);
		std::abort();
	}
	mbstowcs(wfxFilePath, initData.m_fxFilePath, 256);
	m_tkmFile.Load(initData.m_tkmFilePath);

	//�C���X�^���X�̐�����
	m_maxInstance = maxInstance;
	//�C���X�^���X�̐���1��葽���Ƃ�
	if (m_maxInstance > 1)
	{
		InitLevelMat();

		//�C���X�^���V���O�`��p�̍s���v�f��maxInstance�Ń��Z�b�g
		m_instancingMat.reset(new Matrix[m_maxInstance]);
		m_meshParts.InitFromTkmFile(
			m_tkmFile,
			wfxFilePath,
			initData.m_vsEntryPointFunc,
			initData.m_psEntryPointFunc,
			initData.m_expandShaderResoruceView,
			&m_instancingMatricesStructureBuffer,
			m_maxInstance
		);
	}
	else
	{
		m_meshParts.InitFromTkmFile(
			m_tkmFile,
			wfxFilePath,
			initData.m_vsEntryPointFunc,
			initData.m_psEntryPointFunc,
			initData.m_expandShaderResoruceView
		);
	}
	UpdateWorldMatrix(g_vec3Zero, g_quatIdentity, g_vec3One);
}

void Model::UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale)
{
	Matrix mBias;
//todo	if (enUpdateAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(Math::PI * -0.5f);
//	}
	Matrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world = mBias * mScale * mRot * mTrans;
}

void Model::UpdateInstancingData(const Vector3& trans, const Quaternion& rot, const Vector3& scale)
{
	UpdateWorldMatrix(trans, rot, scale);
	if (m_numInstance < m_maxInstance)
	{
		//�C���X�^���V���O�f�[�^���X�V����
		m_instancingMat[m_numInstance] = m_world;
		m_numInstance++;
	}
	else
	{
		//�C���X�^���V���O�`�悷��Ƃ��ɂ��̊֐����Ă�ł�������
		std::abort();
	}

}

void Model::InitLevelMat()
{
	m_instancingMatricesStructureBuffer.Init(
		sizeof(Matrix),
		m_maxInstance,
		m_instancingMat.get()
	);
}

void Model::Draw(RenderContext& rc)
{
	m_meshParts.Draw(
		rc, 
		m_world, 
		g_camera3D->GetViewMatrix(), 
		g_camera3D->GetProjectionMatrix(),
		enRenderMode_Normal,
		IsShadowReciever
	);
}

void Model::Draw(RenderContext& rc,Matrix viewMat,Matrix proMat,int rendermode)
{
	m_meshParts.Draw(
		rc,
		m_world,
		viewMat,
		proMat,
		rendermode,
		IsShadowReciever
	);
}


