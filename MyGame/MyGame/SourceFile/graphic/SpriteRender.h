#pragma once
namespace Engine {
	namespace prefab {
		class SpriteRender:public IGameObject
		{
		public:
			SpriteRender();
			~SpriteRender();

			//�X�V�֐�
			//�����ŌĂ΂�܂�
			void Update();

			//�|�X�g�����_�[
			//�����ŌĂ΂�܂�
			void PostRender();

			//�t�@�C���p�X���Z�b�g
			//Filepath		�t�@�C���p�X
			void Init(const char* Filepath,int height,int width)
			{
				//�t�@�C���p�X���Z�b�g
				m_SpriteInitData.m_ddsFilePath[0] = Filepath;
				//�������w��
				m_SpriteInitData.m_height = height;
				//�����w��
				m_SpriteInitData.m_width = width;
				//�X�v���C�g��������
				m_sprite.Init(m_SpriteInitData);
				//�������t���O�𗧂Ă�
				IsInited = true;
			}

			//�|�W�V�������Z�b�g
			//pos		�ʒu
			void SetPosition(const Vector3& pos)
			{
				m_pos = pos;
			}

			//�g�嗦���Z�b�g
			void SetScale(const Vector3& scale)
			{
				m_scale = scale;
			}

			//��]���Z�b�g
			void SetRotation(const Quaternion& rot)
			{
				m_rot = rot;
			}

			//���̐ݒ�
			//f		���̒l
			void SetAlpha(float f)
			{
				m_sprite.SetAlpha(f);
			}
		private:
			Sprite m_sprite;		//�X�v���C�g
			SpriteInitData m_SpriteInitData;		//�������f�[�^
			Vector3 m_pos = Vector3::Zero;		//�ʒu
			Quaternion m_rot = Quaternion::Identity;		//��]
			Vector3 m_scale = Vector3::One;		//�g�嗦
			Vector2 m_pivot = { 0.5f,0.5f };		//�N�_
			bool IsInited = false;		//�������t���O
		};
	}
}