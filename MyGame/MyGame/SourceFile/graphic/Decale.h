#pragma once

namespace Engine {
	class Decale:Noncopyable
	{
	public:
		Decale();
		~Decale();

		void Init();
		void AddStartPos(const btVector3& start, const btVector3& end)
		{
			//10発に一回だけ弾痕を付ける
			CalcVP(start, end);
		}

		void SetDistance(float dist)
		{
			Distance = dist;
		}

		void Update();

		StructuredBuffer* GetSTB()
		{
			return &m_STB;
		}

		Texture* GetTexture()
		{
			return &m_DecaleTex;
		}
	private:
		std::unique_ptr<Matrix[]> m_DecaleVP;		//デカールのビュープロジェ行列の配列
		int PosNum = 0;		//ポジションの数
		float Distance = 1000;		//デカールを適応する範囲
		StructuredBuffer m_STB;		//ストラクチャーバッファ
		const int m_maxNum = 20;		//ポジションの最大数
		int num = 0;		//現在の数
		Texture m_DecaleTex;		//デカールのテクスチャ
		const float m_SideLength = 10.0f;		//一辺の長さ
		
	private:
		//ビュープロジェ行列を計算して配列に積む
		//pos		
		void CalcVP(const btVector3& start, const btVector3& end);
	};
}