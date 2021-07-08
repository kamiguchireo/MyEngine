#pragma once
#include "Level.h"
#include "SourceFile/graphic/ModelRender.h"
//マップチップのレンダー

struct LevelObjectData;
class MapChipRender:public IGameObject
{
public:
	MapChipRender();
	~MapChipRender();

	void Destroy();
	bool Start();
	void Update();
	
	//描画するオブジェクトの数を追加
	void AddRenderObject(const LevelObjectData& objData,const Matrix& mat)
	{
		m_renderObjDatas.push_back(objData);
		m_levelMatrixs.push_back(mat);
	}

	//すべての描画オブジェクトの追加が終わった後で呼び出す必要がある初期化処理
	void InitAfterAddAllRenderObjects();

	//描画オブジェクトデータにクエリを行う
	void QueryRenderObjDatas(std::function<void(const LevelObjectData& objData)>queryFunc)
	{
		for (const auto& renderObjData : m_renderObjDatas)
		{
			queryFunc(renderObjData);
		}
	}

	void AddRenderObject()
	{
		m_numRenderObject++;
	}

	const Model& GetModel()const
	{
		return m_modelRender->GetModel();
	}

private:
	int m_numRenderObject = 1;
	std::vector<LevelObjectData> m_renderObjDatas;		//描画するオブジェクトの配列
	prefab::ModelRender* m_modelRender = nullptr;		//モデルレンダー
	std::vector<Matrix> m_levelMatrixs;
};

