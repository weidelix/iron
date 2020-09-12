#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include <memory>

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
// Core
#define IRON_CORE_WARN(...)     Iron::Log::GetCoreLogger()->warn (__VA_ARGS__)
#define IRON_CORE_ERROR(...)    Iron::Log::GetCoreLogger()->error(__VA_ARGS__)
#define IRON_CORE_INFO(...)     Iron::Log::GetCoreLogger()->info (__VA_ARGS__)
#define IRON_CORE_TRACE(...)    Iron::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define IRON_CORE_FATAL(...)    Iron::Log::GetCoreLogger()->fatal(__VA_ARGS__)
// CLient
#define DEBUG_WARN(...)               Iron::Log::GetClientLogger()->warn (__VA_ARGS__)
#define DEBUG_ERROR(...)              Iron::Log::GetClientLogger()->error(__VA_ARGS__)
#define DEBUG_INFO(...)               Iron::Log::GetClientLogger()->info (__VA_ARGS__)
#define DEBUG_TRACE(...)              Iron::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DEBUG_FATAL(...)              Iron::Log::GetClientLogger()->fatal(__VA_ARGS__)