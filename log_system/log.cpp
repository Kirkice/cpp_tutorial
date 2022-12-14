//
// Created by Administrator on 2022/12/14.
//

#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::CoreLogger;
std::shared_ptr<spdlog::logger> Log::ClientLogger;

void Log::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    CoreLogger = spdlog::stdout_color_mt("Dist Engine");
    CoreLogger->set_level(spdlog::level::trace);

    ClientLogger = spdlog::stdout_color_mt("Application");
    ClientLogger->set_level(spdlog::level::trace);
}

void Log::Debug(std::string string)
{
    Log::GetCoreLogger()->info(string);
}

void Log::DebugWarn(std::string string)
{
    Log::GetCoreLogger()->warn(string);
}

void Log::DebugError(std::string string)
{
    Log::GetCoreLogger()->error(string);
}