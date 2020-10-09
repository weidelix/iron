#pragma once

#include "pch.h"
#include "Core.h"
#include "Logger.h"

namespace Iron
{
    class IRON_API Log
    {
    private:
        static std::shared_ptr<Iron::Logger> s_ClientLogger;
        static std::shared_ptr<Iron::Logger> s_CoreLogger;
        
    public:
        static void Init();
        inline static std::shared_ptr<Iron::Logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<Iron::Logger>& GetClientLogger() { return s_ClientLogger; }
    };
}

#ifdef IRON_DEBUG
    //DEBUG
    #define IRON_CORE_INFO(...)     Iron::Log::GetCoreLogger()->Info   (__VA_ARGS__)
    #define IRON_CORE_TRACE(...)    Iron::Log::GetCoreLogger()->Trace  (__VA_ARGS__)
    #define IRON_CORE_WARN(...)     Iron::Log::GetCoreLogger()->Warn   (__VA_ARGS__)
    #define IRON_CORE_C_WARN(...)   Iron::Log::GetCoreLogger()->C_Warn (__VA_ARGS__)
    #define IRON_CORE_ERROR(...)    Iron::Log::GetCoreLogger()->Error  (__VA_ARGS__)
    #define IRON_CORE_C_ERROR(...)  Iron::Log::GetCoreLogger()->C_Error(__VA_ARGS__)
    #define IRON_CORE_FATAL(...)    Iron::Log::GetCoreLogger()->Fatal  (__VA_ARGS__)
    #define IRON_CORE_C_FATAL(...)  Iron::Log::GetCoreLogger()->C_Fatal(__VA_ARGS__)
    // CLient
    #define LOG_INFO(...)           Iron::Log::GetClientLogger()->Info   (__VA_ARGS__)
    #define LOG_TRACE(...)          Iron::Log::GetClientLogger()->Trace  (__VA_ARGS__)
    #define LOG_WARN(...)           Iron::Log::GetClientLogger()->Warn   (__VA_ARGS__)
    #define LOG_C_WARN(...)         Iron::Log::GetClientLogger()->C_Warn (__VA_ARGS__)
    #define LOG_ERROR(...)          Iron::Log::GetClientLogger()->Error  (__VA_ARGS__)
    #define LOG_C_ERROR(...)        Iron::Log::GetClientLogger()->C_Error(__VA_ARGS__)
    #define LOG_FATAL(...)          Iron::Log::GetClientLogger()->Fatal  (__VA_ARGS__)                                 
    #define LOG_C_FATAL(...)        Iron::Log::GetClientLogger()->C_Fatal(__VA_ARGS__)                                 
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