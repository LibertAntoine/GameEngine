#pragma once

/* Manage the logging system of the Game Engine */

#include "Core.h"
#include "spdlog/spdlog.h"

namespace GameEngine {
	class GE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// We create macros to call log much faster
// We delete that in production build later to optimage performance.

#define GE_CORE_TRACE(...)       ::GameEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...)        ::GameEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...)        ::GameEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROR(...)       ::GameEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_FATAL(...)       ::GameEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define GE_CLIENT_TRACE(...)     ::GameEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GE_CLIENT_INFO(...)      ::GameEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define GE_CLIENT_WARN(...)      ::GameEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GE_CLIENT_ERROR(...)     ::GameEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define GE_CLIENT_FATAL(...)     ::GameEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

