#include "wipch.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Wi
{
	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("Wi Core");
		s_ClientLogger = spdlog::stdout_color_mt("Wi Client");

		s_CoreLogger->set_level(spdlog::level::info);
		s_ClientLogger->set_level(spdlog::level::info);
	}
}
