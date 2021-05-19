#pragma once

namespace Engine {
	class Decale:Noncopyable
	{
	public:
		Decale();
		~Decale();

		void Init();
		void AddStartPos(const btVector3& start,const btVector3& end)
		{
			m_hogehoge++;
			if (m_hogehoge % 10 == 0) {
				//10���Ɉ�񂾂��e����t����
				CalcVP(start, end);
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
		std::unique_ptr<Matrix[]> m_DecaleVP;		//�f�J�[���̃r���[�v���W�F�s��̔z��
		int PosNum = 0;		//�|�W�V�����̐�
		float Distance = 1000;		//�f�J�[����K������͈�
		StructuredBuffer m_STB;		//�X�g���N�`���[�o�b�t�@
		const int m_maxNum = 20;		//�|�W�V�����̍ő吔
		int num = 0;		//���݂̐�
		Texture m_DecaleTex;		//�f�J�[���̃e�N�X�`��
		const float m_SideLength = 10.0f;		//��ӂ̒���
		int m_hogehoge = 0;		//�ق���
		
	private:
		//�r���[�v���W�F�s����v�Z���Ĕz��ɐς�
		//pos		
		void CalcVP(const btVector3& start, const btVector3& end);
	};
}