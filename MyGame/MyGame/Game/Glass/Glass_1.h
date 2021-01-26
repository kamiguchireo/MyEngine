#pragma once
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
		m_Glass.UpdateInstancingData(trans, rot, scale);
	}
private:
	Model m_Glass;
	ModelInitData m_InitData;
	int m_instanceNum = 1;		//�C���X�^���X�̐�
};