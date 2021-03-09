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
		//初期化
		void Init();

	private:
		//パイプラインステートの初期化
		void InitPipelineState();
		//ディスクリプタヒープの初期化
		void InitDescriptorHeap();

	public:
		//描画開始
		void BeginDraw()
		{
			m_numLine = 0;
		}

		//描画終了
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
		Shader m_vs;		//頂点シェーダー
		Shader m_ps;		//ピクセルシェーダー
		std::unique_ptr<ConstantBuffer> m_cb;		//コンスタントバッファ
		static const int VERTEX_MAX = 4000000;
		std::array<Vector4, VERTEX_MAX> m_VertexBuffer;		//固定長配列

		int m_numLine = 0;

		VertexBuffer m_vBuffer;		//頂点バッファ
		SConstantBuffer s_cb;
		DescriptorHeap m_descriptorHeap;		//ディスクリプタヒープ
		PipelineState m_pipelineState;		//パイプラインステート
		RootSignature m_rootSignature;		//ルートシグネチャ
	};
}
