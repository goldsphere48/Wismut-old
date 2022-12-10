#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Wi
{
	class Log
	{
	public:
		static void Initialize();
		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

#define WI_TRACE(...)		  ::Wi::Log::GetClientLogger()->trace(__VA_ARGS__)
#define WI_INFO(...)		  ::Wi::Log::GetClientLogger()->info(__VA_ARGS__)
#define WI_WARN(...)		  ::Wi::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WI_ERROR(...)		  ::Wi::Log::GetClientLogger()->error(__VA_ARGS__)
#define WI_CRITICAL(...)	  ::Wi::Log::GetClientLogger()->critical(__VA_ARGS__)

#define WI_CORE_TRACE(...)	  ::Wi::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WI_CORE_INFO(...)	  ::Wi::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WI_CORE_WARN(...)	  ::Wi::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WI_CORE_ERROR(...)	  ::Wi::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WI_CORE_CRITICAL(...) ::Wi::Log::GetCoreLogger()->critical(__VA_ARGS__)