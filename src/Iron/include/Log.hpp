#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Iron
{
	class IRON_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}

#ifdef IRON_DEBUG
	// Internal Logging
	#define IRON_CORE_INFO(...)    	SPDLOG_LOGGER_INFO      (Iron::Log::GetCoreLogger(), __VA_ARGS__)
	#define IRON_CORE_TRACE(...)   	SPDLOG_LOGGER_TRACE     (Iron::Log::GetCoreLogger(), __VA_ARGS__)
	#define IRON_CORE_WARN(...)    	SPDLOG_LOGGER_WARN      (Iron::Log::GetCoreLogger(), __VA_ARGS__)
	#define IRON_CORE_ERROR(...)   	SPDLOG_LOGGER_ERROR     (Iron::Log::GetCoreLogger(), __VA_ARGS__)
	#define IRON_CORE_CRITICAL(...)	SPDLOG_LOGGER_CRITICAL  (Iron::Log::GetCoreLogger(), __VA_ARGS__)
	// Client Logging
	#define IRON_INFO(...)           SPDLOG_LOGGER_INFO		(Iron::Log::GetClientLogger(), __VA_ARGS__)
	#define IRON_TRACE(...)          SPDLOG_LOGGER_TRACE     (Iron::Log::GetClientLogger(), __VA_ARGS__)
	#define IRON_WARN(...)           SPDLOG_LOGGER_WARN      (Iron::Log::GetClientLogger(), __VA_ARGS__)
	#define IRON_ERROR(...)          SPDLOG_LOGGER_ERROR     (Iron::Log::GetClientLogger(), __VA_ARGS__)
	#define IRON_FATAL(...)          SPDLOG_LOGGER_CRITICAL  (Iron::Log::GetClientLogger(), __VA_ARGS__) 
								 
#else
	// Core
	#define IRON_CORE_WARN(...) 
	#define IRON_CORE_ERROR(...)
	#define IRON_CORE_INFO(...) 
	#define IRON_CORE_TRACE(...)
	#define IRON_CORE_FATAL(...)
	// CLient
	#define IRON_INFO(...) 
	#define IRON_TRACE(...)
	#define IRON_WARN(...) 
	#define IRON_ERROR(...)
	#define IRON_FATAL(...)
#endif

// // Disable using internal logging for client 
// #ifndef IRON_BUILD_DLL
// 	#define IRON_CORE_INFO(...)
// 	#define IRON_CORE_TRACE(...)
// 	#define IRON_CORE_WARN(...)
// 	#define IRON_CORE_ERROR(...)
// 	#define IRON_CORE_FATAL(...)
// #endif