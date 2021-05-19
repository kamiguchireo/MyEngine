#pragma once
#include "SourceFile/graphic/ModelRender.h"

class Weapon:public IGameObject
{
public:
	Weapon() {}
	~Weapon();
	bool Start();
	void Update();

	//������
	//sk		�X�P���g��
	//IsDither		�f�B�U�����O��K�����邩�ǂ����̃t���O
	void Init(Skeleton* sk,bool IsDither = false);

	//�ˌ�
	void shooting();

private:
	//�f�J�[����ǉ�
	//start		�n�_
	//end		�I�_
	void AddDecale(const btVector3& start, const btVector3& end);

private:
	Skeleton* m_skeleton = nullptr;		//�X�P���g��
	Vector3 m_weaponPos = Vector3::Zero;		//����̃|�W�V����
	Quaternion m_weaponRot = Quaternion::Identity;		//����̉�]
	Matrix m_weaponMat = Matrix::Identity;		//����̍s��
	prefab::ModelRender* m_Model = nullptr;		//���f��
	int LeftHandBoneNo = -1;		//����p�̃{�[���ԍ�
	const float m_range = 1000.0f;		//�˒�
};

