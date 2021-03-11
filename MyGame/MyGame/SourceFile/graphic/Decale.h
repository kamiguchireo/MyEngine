#pragma once

namespace Engine {
	class Decale : public IGameObject
	{
	public:
		Decale();
		~Decale();

		void AddStartPos(const Vector3& pos,const Vector3& dir)
		{
			m_StartPos.push_back(pos);
			m_Direction.push_back(dir);
			PosNum++;
		}

		void SetDistance(float dist)
		{
			Distance = dist;
		}

		bool Start();
		void Update();
	private:
		std::vector<Vector3> m_StartPos;
		std::vector<Vector3> m_Direction;
		std::vector<Matrix> m_DecaleVP;
		int PosNum = 0;
		float Distance = 1000;
	};
}