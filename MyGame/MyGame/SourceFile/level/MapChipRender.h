#pragma once
#include "Level.h"
#include "SourceFile/graphic/ModelRender.h"
//マップチップのレンダー

struct LevelObjectData;
class MapChipRender:public IGameObject
{
public:
	MapChipRender() {}
	~MapChipRender();

	bool Start();
	void Update();
	
private:
	int m_numRenderObject = 0;
	std::vector<LevelObjectData> m_renderObjDatas;		//描画するオブジェクトの配列
	prefab::ModelRender* m_modelRender = nullptr;		//モデルレンダー
};

