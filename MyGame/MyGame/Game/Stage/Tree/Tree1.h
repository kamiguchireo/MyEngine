#pragma once
#include "SourceFile/Physics/PhysicsStaticObject.h"
//#include "SourceFile/graphic/ModelRender.h"

class Tree1:public IGameObject
{
	struct ObjData {
		Vector3 position;		//���W
		Quaternion rotation;	//��]
		Vector3 scale;		//�g�嗦
	};
public:
	Tree1();
	~Tree1();

	bool Start();
	void Update();
	void Draw();

	//�C���X�^���V���O�`�悷��I�u�W�F�N�g�̒ǉ�
	void InitInstance(const Vector3& trans, const Quaternion& rot, const Vector3& scale)
	{
		m_instanceNum = 1;
		ObjData data;
		data.position = trans;
		data.rotation = rot;
		data.scale = scale;
		m_renderObjDatas.push_back(data);
	}
	//�C���X�^���V���O�`�悷��I�u�W�F�N�g�̒ǉ�
	void AddInstance(const Vector3& trans, const Quaternion& rot, const Vector3& scale)
	{
		m_instanceNum++;
		ObjData data;
		data.position = trans;
		data.rotation = rot;
		data.scale = scale;
		m_renderObjDatas.push_back(data);
	}
private:
	prefab::ModelRender* m_Tree = nullptr;
	ModelInitData m_InitData;
	int m_instanceNum = 1;		//�C���X�^���X�̐�
	std::vector<ObjData> m_renderObjDatas;		//�`�悷��I�u�W�F�N�g�̔z��
	std::vector <std::unique_ptr<PhysicsStaticObject>> m_Col;	//�{�b�N�X�R���C�_�[
};

