#pragma once

namespace Engine {
	class Decale
	{
	public:
		Decale();
		~Decale();

		void Init();
		void AddStartPos(const Vector3& pos,const Vector3& right,const Vector3& dir)
		{
			m_StartPos.push_back(pos);
			m_Right.push_back(right);
			m_Direction.push_back(dir);
			PosNum++;
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
		std::vector<Vector3> m_StartPos;
		std::vector<Vector3> m_Right;
		std::vector<Vector3> m_Direction;
		std::unique_ptr<Matrix[]> m_DecaleVP;
		int PosNum = 0;		//ポジションの数
		float Distance = 1000;
		StructuredBuffer m_STB;
		const int m_maxNum = 20;		//ポジションの最大数
		int num = 0;		//現在の数
		Texture m_DecaleTex;
		const float m_SideLength = 5.0f;		//一辺の長さ
	};
}