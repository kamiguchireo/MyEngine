//�N���X�̃R�s�[���֎~�������ꍇ�ɂ�����p�����Ă�������
#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

namespace Engine {
	struct Noncopyable {
		Noncopyable() = default;
		Noncopyable(const Noncopyable&) = delete;
		Noncopyable& operator = (const Noncopyable&) = delete;
	};
}

#endif