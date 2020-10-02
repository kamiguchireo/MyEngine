#pragma once
#include "SourceFile/Noncopyable.h"

namespace Engine {
	typedef unsigned char	GameObjectPrio;

	class IGameObject:Engine::Noncopyable
	{
	public:
		IGameObject():
			m_priority(0),
			m_isDead(false),
			m_isNewFromGameObjectManager(false)
		{
		}
		virtual	~IGameObject()
		{
		}
	
	public:
		//�C�x���g
		enum EnEvent {
			enEvent_Undef,		//����`�C�x���g
			enEvent_Destroy		//�C���X�^���X���j�������
		};

		//�C�x���g�������̃f�[�^
		struct SEventParam {
			EnEvent eEvent = enEvent_Undef;		//�������Ă���C�x���g
			IGameObject*gameObject = nullptr;	//�C�x���g��ʒm���Ă���Q�[���I�u�W�F�N�g�̃C���X�^���X
		};
	public:

	//�A�b�v�f�[�g�O�`��
	virtual void PreRender() {}

	//������
	virtual bool Start() { return true; }

	//�X�V
	virtual void Update() {}
	
	//�`��
	virtual void Draw() {}

	//Render�֐������s���ꂽ��ŌĂ΂��`�揈��
	virtual void PostRender() {}
	public:
		void StartWrapper()
		{
			if (NextRenderStep == StartStep)
			{
				if (!is_StartEnd)
				{
					if (Start()) {
						is_StartEnd = true;
					}
				}
				//���������������B
				NextRenderStep = PreRenderStep;

			}
		}

		void PreRenderWrapper()
		{
			if (NextRenderStep == PreRenderStep)
			{
				if (!m_isDead)
				{
					PreRender();
				}
				NextRenderStep = UpdateStep;
			}
		}

		void UpdateWrapper()
		{
			if (NextRenderStep == UpdateStep)
			{
				if (!m_isDead)
				{
					Update();
				}
				NextRenderStep = DrawStep;
			}
		}

		void DrawWrapper()
		{
			if (NextRenderStep == DrawStep)
			{
				if (!m_isDead)
				{
					Draw();
				}
				NextRenderStep = PostRenderStep;
			}
		}

		void PostRenderWrapper()
		{
			if (NextRenderStep == PostRenderStep)
			{
				if (!m_isDead)
				{
					PostRender();
				}
				NextRenderStep = PreRenderStep;
			}
		}

		void OnDestoroyWrapper()
		{
			SEventParam param;
			param.eEvent = enEvent_Destroy;
			param.gameObject = this;
			//�f�X�g���C�C�x���g�����X�i�[�ɒʒm����B
			for (auto&listener : m_eventListeners)
			{
				listener(param);
			}
		}

		void SetDeadMark()
		{
			m_isDead = true;
		}
		//���S����B
		bool IsDead()const
		{
			return m_isDead;
		}

		GameObjectPrio GetPriority() const
		{
			return m_priority;
		}

		bool IsNewFromGameObjectManagr() const
		{
			return m_isNewFromGameObjectManager;
		}

		friend class CGameObjectManager;
	protected:
		GameObjectPrio	m_priority;			//!<���s�D��x�B
		unsigned int m_nameKey = 0;			//!<���O�L�[�B
		bool m_isRegistDeadList = false;	//!<���S���X�g�ɐς܂�Ă���B
		bool m_isNewFromGameObjectManager;	//!<GameObjectManager��new���ꂽ
		bool m_isRegist = false;			//!<GameObjectManager�ɓo�^����Ă��邩�ǂ���
		bool m_isDead = false;						//!<���S�t���O�B
		bool m_isActive = true;				//Active�t���O
		std::list<std::function<void(SEventParam&eventParam)>> m_eventListeners;	//�C�x���g���X�i�[
		bool is_StartEnd = false;

	private:
	enum GameObjectStep {
		StartStep,
		PreRenderStep,
		UpdateStep,
		DrawStep,
		PostRenderStep
	};
	GameObjectStep NextRenderStep = StartStep;		//�Q�[���I�u�W�F�N�g�}�l�[�W���[���Ŏg�����Ɏ��s������s�X�e�b�v
	};
}