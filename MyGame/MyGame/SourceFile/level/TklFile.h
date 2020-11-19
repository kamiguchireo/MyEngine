#pragma once

//Tkl�t�@�C���̃��[�_�[

class TklFile
{
public:
	struct SObject {
		std::unique_ptr<char[]>name;		//���f���̖��O
		int parentNo;		//�e�̔ԍ�
		float bindPose[4][3];		//�o�C���h�|�[�Y
		float invBindPose[4][3];		//�o�C���h�|�[�Y�̋t��
		int no;		//�I�u�W�F�N�g�̔ԍ�
		bool isShadowCaster;		//�V���h�E�L���X�^�[�t���O
		bool isShadowReciever;		//�V���h�E���V�[�o�[�t���O
		std::vector<int> intDatas;		//int�p�����[�^
		std::vector<float> floatDatas;		//float�p�����[�^
		std::vector<std::unique_ptr<char[]>> charDatas;		//������
		std::vector<Vector3> vec3Datas;		//vector3�̃p�����[�^
	};

	TklFile(){}
	~TklFile(){}
	//�ǂݍ��ݏ���
	//filePath		�t�@�C���p�X
	void Load(const char* filePath);

	//�I�u�W�F�N�g�ɑ΂��ăN�G�����s��
	void QueryObject(std::function<void(SObject& obj)> query)
	{
		for (auto& obj : m_objects)
		{
			query(obj);
		}
	}

private:
	int m_tklVersion = 100;		//tkl�t�@�C���̃o�[�W����
	int m_numObject = 0;		//�I�u�W�F�N�g�̐�
	std::vector<SObject> m_objects;		//�I�u�W�F�N�g�̃��X�g
};

