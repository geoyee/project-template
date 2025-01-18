#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

class LogConfigInit final
{
public:
    LogConfigInit()
    {
        // Create console and file sinks
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        std::string timespec = std::to_string(std::time(nullptr));
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log-" + timespec + ".txt", true);
        // Create combined logger
        spdlog::sinks_init_list sinks = {consoleSink, fileSink};
        static auto combinedLogger = std::make_shared<spdlog::logger>("libraryT", sinks.begin(), sinks.end());
        // Set default logger
        spdlog::register_logger(combinedLogger);
        spdlog::set_default_logger(combinedLogger);
        SPDLOG_INFO("Logger created");
    }
};

static LogConfigInit g_logConfigInit;