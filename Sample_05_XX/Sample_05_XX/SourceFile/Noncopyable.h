//�N���X�̃R�s�[���֎~�������ꍇ�Ɍp������

namespace Engine {
	struct Noncopyable
	{
		Noncopyable() = default;
		Noncopyable(const Noncopyable&) = delete;
		Noncopyable& operator=(const Noncopyable&) = delete;
	};
}