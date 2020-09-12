#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Iron
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%l]%$ %@: %v");
        Log::s_CoreLogger = spdlog::stdout_color_mt("Iron");
        Log::s_CoreLogger->set_level(spdlog::level::trace);
        Log::s_ClientLogger = spdlog::stdout_color_mt("Client");
        Log::s_ClientLogger->set_level(spdlog::level::trace);
    }
}