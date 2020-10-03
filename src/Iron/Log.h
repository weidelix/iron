#pragma once

#include "pch.h"
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Iron
{
    class IRON_API Log
    {
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
        
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    };
}

#ifdef DEBUG

    //DEBUG
    #define IRON_CORE_WARN(...)     Iron::Log::GetCoreLogger()->warn (__VA_ARGS__)
    #define IRON_CORE_ERROR(...)    Iron::Log::GetCoreLogger()->error(__VA_ARGS__)
    #define IRON_CORE_INFO(...)     Iron::Log::GetCoreLogger()->info (__VA_ARGS__)
    #define IRON_CORE_TRACE(...)    Iron::Log::GetCoreLogger()->trace(__VA_ARGS__)
    #define IRON_CORE_FATAL(...)    Iron::Log::GetCoreLogger()->fatal(__VA_ARGS__)
    // CLient
    #define LOG_WARN(...)           Iron::Log::GetClientLogger()->warn (__VA_ARGS__)
    #define LOG_ERROR(...)          Iron::Log::GetClientLogger()->error(__VA_ARGS__)
    #define LOG_INFO(...)           Iron::Log::GetClientLogger()->info (__VA_ARGS__)
    #define LOG_TRACE(...)          Iron::Log::GetClientLogger()->trace(__VA_ARGS__)
    #define LOG_FATAL(...)          Iron::Log::GetClientLogger()->fatal(__VA_ARGS__)
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