#pragma once
#include "Level.h"
#include "SourceFile/graphic/ModelRender.h"
//�}�b�v�`�b�v�̃����_�[

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
	std::vector<LevelObjectData> m_renderObjDatas;		//�`�悷��I�u�W�F�N�g�̔z��
	prefab::ModelRender* m_modelRender = nullptr;		//���f�������_�[
};

