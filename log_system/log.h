//
// Created by Administrator on 2022/12/14.
//

#ifndef LOG_SYSTEM_LOG_H
#define LOG_SYSTEM_LOG_H
#include <string>
#include <spdlog/spdlog.h>


#define SENGINE_LOG_INFO(...)	     LogSystem::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SENGINE_LOG_WARN(...)		 LogSystem::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SENGINE_LOG_ERROR(...)	     LogSystem::Log::GetCoreLogger()->error(__VA_ARGS__)

#define APPLICATION_LOG_INFO(...)	 LogSystem::Log::GetClientLogger()->info(__VA_ARGS__)
#define APPLICATION_LOG_WARN(...)	 LogSystem::Log::GetClientLogger()->warn(__VA_ARGS__)
#define APPLICATION_LOG_ERROR(...)	 LogSystem::Log::GetClientLogger()->error(__VA_ARGS__)

class Log
{
public:
    static void Init();
    static void Debug(std::string string);
    static void DebugWarn(std::string string);
    static void DebugError(std::string string);

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger; }

private:
    static std::shared_ptr<spdlog::logger> CoreLogger;
    static std::shared_ptr<spdlog::logger> ClientLogger;
};


#endif //LOG_SYSTEM_LOG_H
