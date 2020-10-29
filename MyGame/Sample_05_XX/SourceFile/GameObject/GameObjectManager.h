#pragma once
#include "GameObject.h"
#include "util/Util.h"
#include "SourceFile/Noncopyable.h"

namespace Engine {
	class CGameObjectManager:Engine::Noncopyable
	{
	public:
		CGameObjectManager()
		{
			m_gameObjectListArray.resize(20);
			m_deleteObjectArray.resize(20);
		}
		~CGameObjectManager()
		{
		}

	private:
		/*
		�Q�[���I�u�W�F�N�g�̖��O�𐔎��ɕϊ�
		*/
		static unsigned int MakeGameObjectNameKey(const char*objectName)
		{
			//�f�t�H���g�̖��O
			static const unsigned int defaultNameKey = Util::MakeHash("Undefined");
			//�n�b�V���l
			unsigned int hash;
			//���O���Ȃ��Ƃ��f�t�H���g�̖��O������
			if (objectName == nullptr)
			{
				hash = defaultNameKey;
			}
			//���O������Ƃ��͖��O��ϊ�����
			else {
				hash = Util::MakeHash(objectName);
			}
			return hash;
		}

	public:
		//�C���X�^���X�̎擾
		static CGameObjectManager&Instance()
		{
			static CGameObjectManager instance;
			return instance;
		}
		/*
		�Q�[���I�u�W�F�N�g��new
		new������K��delete����
		prio ���s�D�揇�ʁB
		objectName �I�u�W�F�N�g��
		*/
		template<class T>
		T*NewGameObject(GameObjectPrio prio,const char*objectName)
		{
			(void*)objectName;
			T*newObject = new T();
			m_gameObjectListArray[prio].push_back(newObject);
			unsigned int hash = MakeGameObjectNameKey(objectName);
			newObject->m_isRegist = true;
			newObject->m_priority = prio;
			newObject->m_nameKey = hash;
			newObject->m_isNewFromGameObjectManager = true;
			return newObject;
		}

		/*
		�Q�[���I�u�W�F�N�g�̌���
		objectName�@�I�u�W�F�N�g��
		*/
		template<class T>
		T*FindGameObject(const char*objectName)
		{
			unsigned int nameKey = Util::MakeHash(objectName);
			for (auto goList : m_gameObjectListArray)
			{
				for (auto go : goList)
				{
					if (go->m_nameKey == nameKey)
					{
						//������
						T*p = dynamic_cast<T*>(go);
						return p;
					}
				}
			}
			//������Ȃ�����
			throw;
			return nullptr;
		}

		//DeleteGO�̖��O�Ȃ��o�[�W����
		void DeleteGO(IGameObject*go)
		{
			DeleteGameObject(go);
		}
		//DeleteGO�̖��O����o�[�W����
		void DeleteGO(IGameObject*go,const char*objectName)
		{
			//Find����
			go = FindGameObject<IGameObject>(objectName);
			//DeleteGameObject�ɓ����
			DeleteGameObject(go);
		}
		//DeleteGO�̒��g
		void DeleteGameObject(IGameObject*gameObject)
		{
			if (gameObject != nullptr &&gameObject->m_isRegist)
			{
				gameObject->SetDeadMark();
				gameObject->OnDestoroyWrapper();
				gameObject->m_isRegist = false;
				gameObject->m_isRegistDeadList = true;

				m_deleteObjectArray.at(gameObject->GetPriority()).push_back(gameObject);
				gameObject = nullptr;
			}
		}

	public:
		//�X�V�O�`��
		void PreRender();
		//������
		void Start();
		//�X�V
		void Update();
		//�`��
		void Draw();
		//�X�V��`��
		void PostRender();

		//���ׂẴQ�[���I�u�W�F�N�g���폜
		void DeleteAllGameObject();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�S�̂̍X�V
		void Thread()
		{
			Start();
			PreRender();
			Update();
			Draw();
			PostRender();
		}

	private:
		//�Q�[���I�u�W�F�N�g�̍폜�����s
		void ExecuteDeleteGameObjects();

		typedef std::list<IGameObject*>GameObjectList;
		std::vector<GameObjectList> m_gameObjectListArray;		//�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g
		std::vector<GameObjectList> m_deleteObjectArray;		//�폜����I�u�W�F�N�g�̃��X�g�폜�̓r����DeleteGameObject���Ă΂��\���������̂ŁA�_�u���o�b�t�@��
	};

	static inline CGameObjectManager&GameObjectManager()
	{
		return CGameObjectManager::Instance();
	}

	template<class T>
	static inline T*FindGO(const char*objectName)
	{
		return GameObjectManager().FindGameObject<T>(objectName);
	}

	template<class T>
	static inline T*NewGO(int priority,const char*objectName = nullptr, typename T::IGameObject* = nullptr)
	{
		return GameObjectManager().NewGameObject<T>((GameObjectPrio)priority, objectName);
	}

	static inline void DeleteGO(IGameObject*go)
	{
		GameObjectManager().DeleteGameObject(go);
	}

	static inline void DeleteGO(const char*objectName)
	{
		IGameObject*go = FindGO<IGameObject>(objectName);
		GameObjectManager().DeleteGameObject(go);
	}

}