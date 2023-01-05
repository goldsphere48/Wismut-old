#pragma once
#include <memory>

#ifdef WI_DEBUG
	#ifdef WI_PLATFORM_WIN
		#define WI_DEBUGBREAK() __debugbreak()
	#else
		#error "Only windows support"
	#endif
#else
	#define WI_DEBUGBREAK()
#endif

#define WI_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Wi
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	using byte = uint8_t;
}