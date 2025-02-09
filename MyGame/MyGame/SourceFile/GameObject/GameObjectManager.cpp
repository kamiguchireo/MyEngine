#include "stdafx.h"
#include "GameObjectManager.h"

namespace Engine {

	void CGameObjectManager::PreRender()
	{
		for (GameObjectList objList : m_gameObjectListArray)
		{
			for (IGameObject*obj : objList)
			{
				obj->PreRenderWrapper();
			}
		}
	}

	void CGameObjectManager::Start()
	{
		for (GameObjectList objList : m_gameObjectListArray)
		{
			for (IGameObject*obj : objList)
			{
				obj->StartWrapper();

			}
		}
	}

	void CGameObjectManager::Update()
	{
		for (GameObjectList objList : m_gameObjectListArray)
		{
			for (IGameObject*obj : objList)
			{
				obj->UpdateWrapper();
			}
		}
	}

	void CGameObjectManager::Draw()
	{
		for (GameObjectList objList : m_gameObjectListArray)
		{
			for (IGameObject*obj : objList)
			{
				obj->DrawWrapper();
			}
		}
	}

	void CGameObjectManager::PostRender()
	{
		for (GameObjectList objList : m_gameObjectListArray)
		{
			for (IGameObject*obj : objList)
			{
				obj->PostRenderWrapper();
			}
		}
	}
	
	void CGameObjectManager::DeleteAllGameObject()
	{
		for (GameObjectList objList : m_gameObjectListArray)
		{
			for (IGameObject* obj : objList)
			{
				DeleteGO(obj);
			}
		}
		ExecuteDeleteGameObjects();
	}

	void CGameObjectManager::ExecuteDeleteGameObjects()
	{
		for (GameObjectList&goList : m_deleteObjectArray)
		{
			for (IGameObject*go : goList)
			{
				GameObjectPrio prio = go->GetPriority();
				GameObjectList&goExecList = m_gameObjectListArray.at(prio);
				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end())
				{
					//削除リストから除外。
					(*it)->m_isRegistDeadList = false;
					if ((*it)->IsNewFromGameObjectManagr())
					{
						delete(*it);
					}

				}
				goExecList.erase(it);
			}
			goList.clear();
		}
	}



}