#include "Log.h"

namespace Iron
{
    std::shared_ptr<spdlog::logger> s_CoreLogger;
    std::shared_ptr<spdlog::logger> s_ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%l]%$: (%s) %v at \"%!\" line %#");
        s_CoreLogger = spdlog::stdout_color_mt("Iron");
        s_CoreLogger->set_level(spdlog::level::trace);
        s_ClientLogger = spdlog::stdout_color_mt("Client");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}