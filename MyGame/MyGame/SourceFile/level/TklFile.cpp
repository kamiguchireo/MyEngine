#include "stdafx.h"
#include "TklFile.h"

void TklFile::Load(const char* filePath)
{
	//�t�@�C���̃|�C���^
	auto fp = fopen(filePath, "rb");
	if (fp == nullptr)
	{
		//�t�@�C���p�X���Ԉ���Ă��܂��B
		std::abort();
	}

	//tkl�t�@�C���̃o�[�W������ǂݍ���
	fread(&m_tklVersion, sizeof(m_tklVersion), 1, fp);
	//�I�u�W�F�N�g�̐����擾
	fread(&m_numObject, sizeof(m_numObject), 1, fp);
	//�I�u�W�F�N�g�̐���vector�̃��T�C�Y
	m_objects.resize(m_numObject);

	//�I�u�W�F�N�g�̐�������
	for (int i = 0; i < m_numObject; i++)
	{
		auto& obj = m_objects.at(i);
		size_t nameCount = 0;

		//�I�u�W�F�N�g�̖��O���擾
		fread(&nameCount, 1, 1, fp);
		//���f���̖��O�̃��j�[�N�|�C���^���쐬
		obj.name = std::make_unique<char[]>(nameCount + 1);
		fread(obj.name.get(), nameCount + 1, 1, fp);

		//�e��ID���擾
		fread(&obj.parentNo, sizeof(obj.parentNo), 1, fp);

		//�o�C���h�|�[�Y���擾
		fread(obj.bindPose, sizeof(obj.bindPose), 1, fp);

		//�o�C���h�|�[�Y�̋t�����擾
		fread(obj.invBindPose, sizeof(obj.invBindPose), 1, fp);

		//�I�u�W�F�N�g�̔ԍ�
		obj.no = i;

		//�V���h�E�L���X�^�[�̃t���O
		fread(&obj.isShadowCaster, sizeof(obj.isShadowCaster), 1, fp);

		//�V���h�E���V�[�o�[�̃t���O
		fread(&obj.isShadowReciever, sizeof(obj.isShadowReciever), 1, fp);

		//int�p�����[�^�̐�
		int numIntData;
		fread(&numIntData, sizeof(numIntData), 1, fp);
		//int�p�����[�^�̐��Ń��T�C�Y
		obj.intDatas.resize(numIntData);
		//int�p�����[�^�̐�����
		for (int i = 0; i < numIntData; i++)
		{
			int val = 0;
			//int�^�Ŏ擾
			fread(&val, sizeof(val), 1, fp);
			obj.intDatas.push_back(val);
		}

		//float�p�����[�^�̐�
		int numFloatData;
		fread(&numFloatData, sizeof(numFloatData), 1, fp);
		//float�p�����[�^�̐��Ń��T�C�Y
		obj.floatDatas.resize(numFloatData);
		//float�p�����[�^�̐�����
		for (int i = 0; i < numFloatData; i++)
		{
			float val = 0;
			//float�^�Ŏ擾
			fread(&val, sizeof(val), 1, fp);
			obj.floatDatas.push_back(val);
		}

		//string�p�����[�^�̐�
		int numStringData;
		fread(&numStringData, sizeof(numStringData), 1, fp);
		//string�p�����[�^�̐��Ń��T�C�Y
		obj.charDatas.resize(numStringData);
		//string�p�����[�^�̐�������
		for (int i = 0; i < numStringData; i++)
		{
			//string�p�����[�^�̒���
			int numChara;
			fread(&numChara, sizeof(numChara), 1, fp);
			//string�p�����[�^
			obj.charDatas[i] = std::make_unique<char[]>(numChara + 1);
			fread(obj.charDatas[i].get(), numChara + 1, 1, fp);
		}

		//vector3�p�����[�^�̐�
		int numVec3Data;
		fread(&numVec3Data, sizeof(numVec3Data), 1, fp);
		//vector3�p�����[�^
		for (int i = 0; i < numVec3Data; i++)
		{
			float x, y, z;
			fread(&x, sizeof(x), 1, fp);
			fread(&y, sizeof(y), 1, fp);
			fread(&z, sizeof(z), 1, fp);
			obj.vec3Datas.push_back(Vector3(x, y, z));
		}
	}
	//�t�@�C�������
	fclose(fp);
}