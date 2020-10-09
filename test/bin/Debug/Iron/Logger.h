#pragma once
#include "Core.h"
#include "pch.h"
#include <fmt/format.h>
#include <fmt/color.h>

enum LogLevel
{
    Trace,
    Info,
    Warn,
    Error,
    Fatal,
};

namespace Iron
{
    class IRON_API Logger
    {
    private:
        std::string&& m_tLogLevelMessage = std::string("TRACE");
        std::string&& m_iLogLevelMessage = std::string("INFO");
        std::string&& m_wLogLevelMessage = std::string("WARN");
        std::string&& m_eLogLevelMessage = std::string("ERROR");
        std::string&& m_fLogLevelMessage = std::string("FATAL");

        LogLevel m_logLevel = LogLevel::Trace;

    public:
        Logger() {}
        Logger(LogLevel level)
            :m_logLevel(level) {}
        ~Logger() {}

        template<class... Args>
        void Trace(std::string message, Args&&... args)
        {
            if (LogLevel::Trace >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::wheat),"[{0}]", m_iLogLevelMessage));
                fmt::print(message.c_str(), args...);
            }
        }
        template<class... Args>
        void Info(std::string message, Args&&... args)
        {
            if (LogLevel::Info >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::yellow_green),"[{0}]", m_iLogLevelMessage));
                fmt::print(message.c_str(), args...);
            }
        }
        template<class... Args>
        void Error(std::string message, Args&&... args)
        {
            if (LogLevel::Error >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::red),"[{0}]", m_eLogLevelMessage));
                fmt::print(message.c_str(), args...);
            }
        }
        template<class... Args>
        void C_Error(std::string loglevelmessage, std::string message, Args&&... args)
        {
            if (LogLevel::Error >= m_logLevel)
            {
                SetLogLevelMessage(LogLevel::Error, loglevelmessage);
                fmt::print("{0}: ", fmt::format(fg(fmt::color::red),"[{0}]", m_eLogLevelMessage),":");
                fmt::print(message.c_str(), args...);
                SetLogLevelMessage(LogLevel::Error, "ERROR");
            }
        }
        template<class... Args>
        void Warn(std::string message, Args&&... args)
        {
            if (LogLevel::Warn >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::yellow),"[{0}]", m_wLogLevelMessage),":");
                fmt::print(message.c_str(), args...);
            }
        }
        template<class... Args>
        void C_Warn(std::string loglevelmessage, std::string message, Args&&... args)
        {
            if (LogLevel::Warn >= m_logLevel)
            {
                SetLogLevelMessage(LogLevel::Warn, loglevelmessage);
                fmt::print("{0}: ", fmt::format(fg(fmt::color::yellow),"[{0}]", m_wLogLevelMessage),":");
                fmt::print(message.c_str(), args...);
                SetLogLevelMessage(LogLevel::Warn, "WARN");
            }
        }
        template<class... Args>
        void Fatal(std::string message, Args&&... args)
        {
            if (LogLevel::Fatal >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::dark_red),"[{0}]", m_fLogLevelMessage),":");
                fmt::print(message.c_str(), args...);
            }
        }
        template<class... Args>
        void C_Fatal(std::string loglevelmessage, std::string message, Args&&... args)
        {
            if (LogLevel::Fatal >= m_logLevel)
            {
                SetLogLevelMessage(LogLevel::Fatal, loglevelmessage);
                fmt::print("{0}: ", fmt::format(fg(fmt::color::dark_red),"[{0}]", m_fLogLevelMessage),":");
                fmt::print(message.c_str(), args...);
                SetLogLevelMessage(LogLevel::Fatal, "FATAL");
            }
        }
        template<class... Args>
        std::basic_string<char> Format(std::string message, Args&&... args)
        {
            return fmt::format(message, args...);
        }

        void SetLogLevelMessage(LogLevel level,  std::string loglevelmessage);
        void SetLogLevel(LogLevel level);
    };
}