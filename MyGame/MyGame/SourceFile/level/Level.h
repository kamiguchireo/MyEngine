#pragma once

class MapChip;
class MapChipRender;

struct LevelObjectData {
	Vector3 position;		//���W
	Quaternion rotation;	//��]
	Vector3 scale;		//�g�嗦
	const wchar_t* name;		//���O
	bool isShadowCaster;		//�V���h�E�L���X�^�[
	bool isShadowReciever;		//�V���h�E���V�[�o�[
};

class Level:Noncopyable
{
private:
	using MapChipPtr = std::unique_ptr<MapChip>;
	using MapChipRenderPtr = std::unique_ptr<MapChipRender>;

public:
	Level() {}
	~Level();

	//���x���̏�����
	//filePath		tkl�t�@�C���̃t�@�C���p�X
	//hoolFunc		�I�u�W�F�N�g���쐬����Ƃ��̃t�b�N�֐�
	//�t�b�N���Ȃ��Ƃ���nullptr���w�肵�Ă�������
	//�f�t�H���g�ō쐬�����MapChip�N���X�̃C���X�^���X���s�v�ȏꍇ��true��Ԃ��Ă�������
	void Init(const char* filePath, std::function<bool(LevelObjectData& objData)> hookFunc);
};

