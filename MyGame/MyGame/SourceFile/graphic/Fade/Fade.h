#pragma once
#include "SourceFile/Graphic/SpriteRender.h"

namespace Engine {
	class Fade
	{
	public:
		Fade();
		~Fade();

		bool Init();
		void Update();
		//�t�F�[�h�C��
		void FadeIn();
		//�t�F�[�h�A�E�g
		void FadeOut();
		//�t�F�[�h�X�s�[�h��ύX
		void SetFadeSpeed(float f)
		{
			m_FadeSpeed = f;
		}
		//�t�F�[�h�����ς݂��ǂ���
		bool IsEnded()const
		{
			return m_IsDirty;
		}
		float GetAlpha()
		{
			return m_Alpha;
		}
	private:
		prefab::SpriteRender* m_sprite = nullptr;		//�X�v���C�g
		bool m_IsDirty = false;		//�X�V���K�v���ǂ����̃t���O
		float m_FadeSpeed = 0.2f;		//�t�F�[�h�X�s�[�h
		float m_Alpha = 0.0f;		//���݂̃�
		float m_NextAlpha = 0.0f;		//���̃�
		float interpolate = 0.0f;		//�⊮��
	};
}