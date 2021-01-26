#pragma once

struct ObjData {
	Vector3 position;		//���W
	Quaternion rotation;	//��]
	Vector3 scale;		//�g�嗦
};
class Glass_1:public IGameObject
{
public:
	Glass_1();
	~Glass_1();

	bool Start();
	void Update();
	void Draw();

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
	Model m_Glass;
	ModelInitData m_InitData;
	int m_instanceNum = 1;		//�C���X�^���X�̐�
	std::vector<ObjData> m_renderObjDatas;		//�`�悷��I�u�W�F�N�g�̔z��
};