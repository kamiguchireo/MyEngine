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
		void Init();
		void BeginDraw(RenderContext& rc)
		{
			m_renderContext = &rc;
			m_numLine = 0;
		}

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
		int m_debugMode = btIDebugDraw::DBG_NoDebug;
		RenderContext* m_renderContext = nullptr;
		Shader m_vs;		//���_�V�F�[�_�[
		Shader m_ps;		//�s�N�Z���V�F�[�_�[
		ConstantBuffer m_cb;		//�R���X�^���g�o�b�t�@
		static const int VERTEX_MAX = 1000000;
		std::array<Vector4, VERTEX_MAX> m_vertexBuffer;		//�Œ蒷�z��

		int m_numLine = 0;
	};
}
