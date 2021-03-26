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
			m_hogehoge++;
			if (m_hogehoge % 10 == 0) {
				//10���Ɉ�񂾂��e����t����
				CalcVP(pos, right, dir);
			}
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
		
		std::unique_ptr<Matrix[]> m_DecaleVP;
		int PosNum = 0;		//�|�W�V�����̐�
		float Distance = 1000;
		StructuredBuffer m_STB;
		const int m_maxNum = 20;		//�|�W�V�����̍ő吔
		int num = 0;		//���݂̐�
		Texture m_DecaleTex;
		const float m_SideLength = 5.0f;		//��ӂ̒���
		int m_hogehoge = 0;
		
	private:
		void CalcVP(const Vector3& pos, const Vector3& right, const Vector3& dir);
	};
}