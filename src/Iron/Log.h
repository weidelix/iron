#pragma once

#include "pch.h"
#include "Core.h"
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
    //DEBUG
    #define IRON_CORE_INFO(...)     SPDLOG_LOGGER_INFO      (Iron::Log::GetCoreLogger(), __VA_ARGS__)
    #define IRON_CORE_TRACE(...)    SPDLOG_LOGGER_TRACE     (Iron::Log::GetCoreLogger(), __VA_ARGS__)
    #define IRON_CORE_WARN(...)     SPDLOG_LOGGER_WARN      (Iron::Log::GetCoreLogger(), __VA_ARGS__)
    #define IRON_CORE_ERROR(...)    SPDLOG_LOGGER_ERROR     (Iron::Log::GetCoreLogger(), __VA_ARGS__)
    #define IRON_CORE_CRITICAL(...) SPDLOG_LOGGER_CRITICAL  (Iron::Log::GetCoreLogger(), __VA_ARGS__)
    // CLient
    #define LOG_INFO(...)           SPDLOG_LOGGER_INFO      (Iron::Log::GetClientLogger(), __VA_ARGS__)
    #define LOG_TRACE(...)          SPDLOG_LOGGER_TRACE     (Iron::Log::GetClientLogger(), __VA_ARGS__)
    #define LOG_WARN(...)           SPDLOG_LOGGER_WARN      (Iron::Log::GetClientLogger(), __VA_ARGS__)
    #define LOG_ERROR(...)          SPDLOG_LOGGER_ERROR     (Iron::Log::GetClientLogger(), __VA_ARGS__)
    #define LOG_FATAL(...)          SPDLOG_LOGGER_CRITICAL  (Iron::Log::GetClientLogger(), __VA_ARGS__) 
                                 
#else
    // Core
    #define IRON_CORE_WARN(...) 
    #define IRON_CORE_ERROR(...)
    #define IRON_CORE_INFO(...) 
    #define IRON_CORE_TRACE(...)
    #define IRON_CORE_FATAL(...)
    // CLient
    #define LOG_WARN(...) 
    #define LOG_ERROR(...)
    #define LOG_INFO(...) 
    #define LOG_TRACE(...)
    #define LOG_FATAL(...)
#endif