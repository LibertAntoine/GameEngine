#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace GameEngine {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$"); // Define with a pattern the form of the console message, here "[timestamp] consoleName : name"
		s_CoreLogger = spdlog::stdout_color_mt("GameEngine"); // Give alert console name type
		s_CoreLogger->set_level(spdlog::level::trace); // Give alert level

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace); // Give color

	}

}