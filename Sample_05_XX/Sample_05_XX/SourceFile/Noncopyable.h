//クラスのコピーを禁止したい場合に継承する

namespace Engine {
	struct Noncopyable
	{
		Noncopyable() = default;
		Noncopyable(const Noncopyable&) = delete;
		Noncopyable& operator=(const Noncopyable&) = delete;
	};
}