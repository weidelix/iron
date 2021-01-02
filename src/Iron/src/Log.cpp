#include "Log.hpp"

namespace Iron
{
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	 
	void Log::Init()
	{
		spdlog::set_pattern("%^[%l]%$: %oms -- %@ - %v");

		s_CoreLogger = spdlog::stdout_color_mt("Iron");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->set_pattern("%^[%l]%$: %oms -- %@ - %v");
		
		s_ClientLogger = spdlog::stdout_color_mt("Client");
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_pattern("%^[%l]%$: %oms -- %@ - %v");
	}
}
