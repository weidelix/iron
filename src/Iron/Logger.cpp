#include "Logger.h"

namespace Iron
{
    void Logger::SetLogLevelMessage(LogLevel level, std::string loglevelmessage)
    {
        if (level == LogLevel::Trace) m_tLogLevelMessage = loglevelmessage;
        if (level == LogLevel::Info ) m_iLogLevelMessage = loglevelmessage;
        if (level == LogLevel::Warn ) m_wLogLevelMessage = loglevelmessage;
        if (level == LogLevel::Error) m_eLogLevelMessage = loglevelmessage;
        if (level == LogLevel::Fatal) m_fLogLevelMessage = loglevelmessage;
    }
    void Logger::SetLogLevel(LogLevel level)
    {
        m_logLevel = level;
    }
}