#pragma once
#include <array>

namespace Engine {
	class PhysicsDebugDraw :public btIDebugDraw
	{
		struct SConstantBuffer {
			Matrix mView;
			Matrix mProj;
		};

	public:
		PhysicsDebugDraw();
		~PhysicsDebugDraw(){}
		//������
		void Init();

	private:
		//�p�C�v���C���X�e�[�g�̏�����
		void InitPipelineState();
		//�f�B�X�N���v�^�q�[�v�̏�����
		void InitDescriptorHeap();

	public:
		//�`��J�n
		void BeginDraw()
		{
			m_numLine = 0;
		}

		//�`��I��
		void EndDraw();

		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

		void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) override
		{
		}
		void reportErrorWarning(const char*) override
		{
		}
		void draw3dText(const btVector3&, const char*) override
		{
		}
		void setDebugMode(int debugMode) override
		{
			m_debugMode = debugMode;
		}
		int	getDebugMode() const override
		{
			return m_debugMode;
		}

	private:
		int m_debugMode = btIDebugDraw::DBG_DrawWireframe;
		Shader m_vs;		//���_�V�F�[�_�[
		Shader m_ps;		//�s�N�Z���V�F�[�_�[
		std::unique_ptr<ConstantBuffer> m_cb;		//�R���X�^���g�o�b�t�@
		static const int VERTEX_MAX = 4000000;
		std::array<Vector4, VERTEX_MAX> m_VertexBuffer;		//�Œ蒷�z��

		int m_numLine = 0;

		VertexBuffer m_vBuffer;		//���_�o�b�t�@
		SConstantBuffer s_cb;
		DescriptorHeap m_descriptorHeap;		//�f�B�X�N���v�^�q�[�v
		PipelineState m_pipelineState;		//�p�C�v���C���X�e�[�g
		RootSignature m_rootSignature;		//���[�g�V�O�l�`��
	};
}
