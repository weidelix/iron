#include "Log.h"


namespace Iron
{
    std::shared_ptr<Iron::Logger> Log::s_ClientLogger;
    std::shared_ptr<Iron::Logger> Log::s_CoreLogger;
    
    void Log::Init()
    {
        Log::s_ClientLogger = std::shared_ptr<Iron::Logger>(new Logger());
        Log::s_CoreLogger = std::shared_ptr<Iron::Logger>(new Logger());
    }
}