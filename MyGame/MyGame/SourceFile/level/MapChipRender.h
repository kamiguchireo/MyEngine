#pragma once
#include "Level.h"
#include "SourceFile/graphic/ModelRender.h"
//�}�b�v�`�b�v�̃����_�[

struct LevelObjectData;
class MapChipRender:public IGameObject
{
public:
	MapChipRender();
	~MapChipRender();

	bool Start();
	void Update();
	
	//�`�悷��I�u�W�F�N�g�̐���ǉ�
	void AddRenderObject(const LevelObjectData& objData)
	{
		m_renderObjDatas.push_back(objData);
	}

	//���ׂĂ̕`��I�u�W�F�N�g�̒ǉ����I�������ŌĂяo���K�v�����鏉��������
	void InitAfterAddAllRenderObjects();

	//�`��I�u�W�F�N�g�f�[�^�ɃN�G�����s��
	void QueryRenderObjDatas(std::function<void(const LevelObjectData& objData)>queryFunc)
	{
		for (const auto& renderObjData : m_renderObjDatas)
		{
			queryFunc(renderObjData);
		}
	}
private:
	int m_numRenderObject = 0;
	std::vector<LevelObjectData> m_renderObjDatas;		//�`�悷��I�u�W�F�N�g�̔z��
	prefab::ModelRender* m_modelRender = nullptr;		//���f�������_�[
};

