#pragma once
#include <spdlog/spdlog.h>

namespace Wi
{
	class Log
	{
	public:
		static void Initialize();
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define WI_INFO(...)		  ::Wi::Log::GetClientLogger()->info(__VA_ARGS__)
#define WI_WARN(...)		  ::Wi::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WI_ERROR(...)		  ::Wi::Log::GetClientLogger()->error(__VA_ARGS__)
#define WI_CRITICAL(...)	  ::Wi::Log::GetClientLogger()->critical(__VA_ARGS__)

#define WI_CORE_INFO(...)	  ::Wi::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WI_CORE_WARN(...)	  ::Wi::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WI_CORE_ERROR(...)	  ::Wi::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WI_CORE_CRITICAL(...) ::Wi::Log::GetCoreLogger()->critical(__VA_ARGS__)