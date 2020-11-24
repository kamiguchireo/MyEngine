#pragma once
#include "TklFile.h"

class MapChip;
class MapChipRender;

struct LevelObjectData {
	Vector3 position;		//���W
	Quaternion rotation;	//��]
	Vector3 scale;		//�g�嗦
	const wchar_t* name = nullptr;		//���O
	bool isShadowCaster = true;		//�V���h�E�L���X�^�[
	bool isShadowReciever = true;		//�V���h�E���V�[�o�[
};

class Level:Noncopyable
{
private:
	using MapChipPtr = std::unique_ptr<MapChip>;
	using MapChipRenderPtr = std::unique_ptr<MapChipRender>;

public:
	Level();
	~Level();

	//���x���̏�����
	//filePath		tkl�t�@�C���̃t�@�C���p�X
	//hoolFunc		�I�u�W�F�N�g���쐬����Ƃ��̃t�b�N�֐�
	//�t�b�N���Ȃ��Ƃ���nullptr���w�肵�Ă�������
	//�f�t�H���g�ō쐬�����MapChip�N���X�̃C���X�^���X���s�v�ȏꍇ��true��Ԃ��Ă�������
	void Init(const char* filePath, std::function<bool(LevelObjectData& objData)> hookFunc);

private:
	//�}�b�v�`�b�v�����_�[���쐬���邩�A�`�悷��I�u�W�F�N�g���C���N�������g����
	//���o�^�̃I�u�W�F�N�g���n���ꂽ��A�����_�[���쐬����
	//�o�^�ς݂̏ꍇ�́A�}�b�v�`�b�v�����_�[���`�悷�ׂ��I�u�W�F�N�g���C���N�������g����
	MapChipRender* CreateMapChipRenderOrAddRenderObject(const LevelObjectData& objData,int i);
	//�{�[���s��̍\�z
	void BuildBoneMatrices();
private:
	std::map<unsigned int, MapChipRender*>m_mapChipRenderPtrs;		//�}�b�v�`�b�v�����_�[�̔z��
	std::vector<MapChipPtr> m_mapChipPtrs;			//�}�b�v�`�b�v�̔z��
	TklFile m_tklFile;
	using BonePtr = std::unique_ptr<Bone>;
	std::vector<BonePtr> m_bones;
	std::unique_ptr<Matrix[]>	m_boneMatrixs;		//�{�[���s��
	bool m_isInited = false;						//�������t���O

};