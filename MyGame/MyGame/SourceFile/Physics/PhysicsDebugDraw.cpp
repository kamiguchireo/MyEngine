#include "stdafx.h"
#include "PhysicsDebugDraw.h"

namespace Engine {

	PhysicsDebugDraw::PhysicsDebugDraw()
	{
		m_cb = std::make_unique<ConstantBuffer>();
	}
	void PhysicsDebugDraw::Init()
	{
		//頂点バッファの作成
		m_vBuffer.Init(static_cast<int>(m_VertexBuffer.size()),sizeof(Vector4));
		m_vBuffer.Copy((void*)&m_VertexBuffer[0]);

		g_graphicsEngine->GetRenderContext().SetVertexBuffer(m_vBuffer);
		m_vs.LoadVS(L"Assets/shader/linePrimitive.fx", "VSMain");
		m_ps.LoadPS(L"Assets/shader/linePrimitive.fx", "PSMain");
		//コンスタントバッファの作成
		m_cb->Init(sizeof(s_cb),&s_cb);

		//ルートシグネチャを初期化
		m_rootSignature.Init(
			D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP
		);

		//パイプラインステートの描画
		InitPipelineState();
		//ディスクリプタヒープの初期化
		InitDescriptorHeap();
	}

	void PhysicsDebugDraw::InitPipelineState()
	{
		//頂点レイアウトを定義する
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "SV_Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		};

		//パイプラインステートを作成
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
		psoDesc.InputLayout = { inputElementDescs,_countof(inputElementDescs) };
		psoDesc.pRootSignature = m_rootSignature.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vs.GetCompiledBlob());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_ps.GetCompiledBlob());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = TRUE;
		psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		//始点と終点からワイヤーフレーム表示する
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;		//アルベドカラー出力用
		psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		psoDesc.SampleDesc.Count = 1;

		m_pipelineState.Init(psoDesc);
	}

	void PhysicsDebugDraw::InitDescriptorHeap()
	{
		//ディスクリプタヒープに定数バッファをセット
		m_descriptorHeap.RegistConstantBuffer(0,*m_cb);
		m_descriptorHeap.Commit();
	}

	void PhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& /*color*/)
	{
		int baseIndex = m_numLine * 2;
		
		//頂点バッファにセット
		m_VertexBuffer[baseIndex].Set(Vector3(from.x(), from.y(), from.z()));
		m_VertexBuffer[baseIndex + 1].Set(Vector3(to.x(), to.y(), to.z()));
		
		m_numLine++;
	}

	void PhysicsDebugDraw::EndDraw()
	{
		m_vBuffer.Copy((void*)&m_VertexBuffer[0]);
		//定数バッファの更新
		s_cb.mView = g_camera3D->GetViewMatrix();
		s_cb.mProj = g_camera3D->GetProjectionMatrix();
		m_cb->CopyToVRAM(&s_cb);
		//ルートシグネチャを設定。
		g_graphicsEngine->GetRenderContext().SetRootSignature(m_rootSignature);
		//パイプラインステートを設定。
		g_graphicsEngine->GetRenderContext().SetPipelineState(m_pipelineState);
		//頂点バッファを設定。
		g_graphicsEngine->GetRenderContext().SetVertexBuffer(m_vBuffer);
		//プリミティブトポロジーを設定する。
		g_graphicsEngine->GetRenderContext().SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		//ディスクリプタヒープを設定する。
		g_graphicsEngine->GetRenderContext().SetDescriptorHeap(m_descriptorHeap);
		//描画する
		g_graphicsEngine->GetRenderContext().Draw(m_numLine * 2);
	}
}