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
        std::string m_tLogLevelMessage = std::string("TRACE");
        std::string m_iLogLevelMessage = std::string("INFO");
        std::string m_wLogLevelMessage = std::string("WARN");
        std::string m_eLogLevelMessage = std::string("ERROR");
        std::string m_fLogLevelMessage = std::string("FATAL");

        std::string m_defaultFormat = "{:#.}";

        LogLevel m_logLevel = LogLevel::Trace;

    public:
        Logger() {}
        Logger(LogLevel level)
            :m_logLevel(level) {}
        ~Logger() {}

        template<class T, class... Args>
        void Trace(T& message, Args&&... args)
        {
            if (LogLevel::Trace >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::wheat),"[{0}]", m_iLogLevelMessage));
                fmt::print(message, args...);
            }
        }

        template<class T, class... Args>
        void Info(T& message, Args&&... args)
        {
            if (LogLevel::Info >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::yellow_green),"[{0}]", m_iLogLevelMessage));
                fmt::print(message, args...);
            }
        }

        template<class T, class... Args>
        void Error(T& message, Args&&... args)
        {
            if (LogLevel::Error >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::red),"[{0}]", m_eLogLevelMessage));
                fmt::print(message, args...);
            }
        }

        template<class T, class... Args>
        void C_Error(T& loglevelMessage, std::string message, Args&&... args)
        {
            if (LogLevel::Error >= m_logLevel)
            {
                SetLogLevelMessage(LogLevel::Error, loglevelMessage);
                fmt::print("{0}: ", fmt::format(fg(fmt::color::red),"[{0}]", loglevelMessage));
                fmt::print(message, args...);
                SetLogLevelMessage(LogLevel::Error, "ERROR");
            }
        }

        template<class T, class... Args>
        void Warn(T& message, Args&&... args)
        {
            if (LogLevel::Warn >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::yellow),"[{0}]", m_wLogLevelMessage));
                fmt::print(message, args...);
            }
        }

        template<class T, class... Args>
        void C_Warn(T& loglevelMessage, std::string message, Args&&... args)
        {
            if (LogLevel::Warn >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::yellow),"[{0}]", loglevelMessage));
                fmt::print(message, args...);
            }
        }

        template<class T, class... Args>
        void Fatal(T& message, Args&&... args)
        {
            if (LogLevel::Fatal >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::red),"[{0}]", m_fLogLevelMessage));
                fmt::print(message, args...);
            }
        }

        template<class T, class... Args>
        void C_Fatal(T& loglevelMessage, std::string message, Args&&... args)
        {
            if (LogLevel::Fatal >= m_logLevel)
            {
                fmt::print("{0}: ", fmt::format(fg(fmt::color::red),"[{0}]", logLevelMessage));
                fmt::print(message, args...);
            }
        }

        template<class T, class... Args>
        std::basic_string<char> Format(T& message, Args&&... args)
        {
            return fmt::format(message, args...);
        }

        void SetLogLevelMessage(LogLevel level,  std::string loglevelMessage);
        void SetLogLevel(LogLevel level);
    };
}