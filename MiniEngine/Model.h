#pragma once

#include "tkFile/TkmFile.h"
#include "MeshParts.h"
#include "Skeleton.h"

class IShaderResource;

/// <summary>
/// ���f���̏������f�[�^
/// </summary>
struct ModelInitData {
	const char* m_tkmFilePath = nullptr;		//tkm�t�@�C���p�X�B
	const char* m_vsEntryPointFunc = "VSMain";	//���_�V�F�[�_�[�̃G���g���[�|�C���g�B
	const char* m_psEntryPointFunc = "PSMain";	//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g�B
	const char* m_fxFilePath = nullptr;			//.fx�t�@�C���̃t�@�C���p�X�B
	IShaderResource* m_expandShaderResoruceView = nullptr;	//���[�U�[�g���̃V�F�[�_�[���\�[�X�B
};
/// <summary>
/// ���f���N���X�B
/// </summary>
class Model {

public:

	/// <summary>
	/// tkm�t�@�C�����珉�����B
	/// </summary>
	/// <param name="initData">�������f�[�^</param>
	void Init(const ModelInitData& initData,int m_maxInstance = 1);
	/// <summary>
	/// ���[���h�s��̍X�V�B
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale);

	//�C���X�^���V���O�`��p�̃f�[�^�̍X�V
	void UpdateInstancingData(const Vector3& trans,const Quaternion& rot,const Vector3& scale);

	/// <summary>
	/// �X�P���g�����֘A�t����B
	/// </summary>
	/// <param name="skeleton">�X�P���g��</param>
	void BindSkeleton(Skeleton& skeleton)
	{
		m_meshParts.BindSkeleton(skeleton);
	}

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="renderContext">�����_�����O�R���e�L�X�g</param>
	void Draw(RenderContext& renderContext);
	void Draw(RenderContext& renderContext,Matrix viewMat,Matrix proMat,int rendermode = 1);

	/// <summary>
	/// ���[���h�s����擾�B
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

	void Refresh()
	{
		m_numInstance = 0;
	}

	void InitLevelMat();
private:
	Matrix m_world;			//���[���h�s��B
	TkmFile m_tkmFile;		//tkm�t�@�C���B
	MeshParts m_meshParts;	//���b�V���p�[�c�B
	bool IsShadowReciever = false;
	int m_numInstance = 0;
	int m_maxInstance = 1;
	std::unique_ptr<Matrix[]> m_instancingMat;		//�C���X�^���V���O�`��p�̍s��
	StructuredBuffer m_instancingMatricesStructureBuffer;		//�C���X�^���V���O�`��p�̃o�b�t�@
};