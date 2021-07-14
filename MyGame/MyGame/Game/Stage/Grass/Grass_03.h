#pragma once


class Grass_03:public IGameObject
{
	struct ObjData {
		Vector3 position;		//���W
		Quaternion rotation;	//��]
		Vector3 scale;		//�g�嗦
	};
public:
	Grass_03();
	~Grass_03();

	void OnDestroy();
	bool Start();
	void Update();

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
	prefab::ModelRender* m_Glass = nullptr;
	int m_instanceNum = 1;		//�C���X�^���X�̐�
	std::vector<ObjData> m_renderObjDatas;		//�`�悷��I�u�W�F�N�g�̔z��
};