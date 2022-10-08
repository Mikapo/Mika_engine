#include "Debug_logger.h"
#include "gsl/gsl"
#include <GL/glew.h>
#include <chrono>
#include <ctime>
#include <fstream>

namespace MEngine
{
    std::string Debug_logger::get_time_string() const
    {
        using namespace std::chrono;

        const auto current_time = system_clock::now();
        const time_t time = system_clock::to_time_t(current_time);

        std::array<char, 26> buffer;
        ctime_s(buffer.data(), buffer.size(), &time);
        const std::string time_string = buffer.data();

        return time_string.substr(11, 8);
    }

    Debug_logger& Debug_logger::get() noexcept
    {
        static Debug_logger logger;
        return logger;
    }

    void Debug_logger::log(Log_severity severity, Log_type type, std::string_view msg)
    {
        if (!is_log_alloved(severity, type))
            return;

        const std::string current_time = get_time_string();
        const std::string_view severity_string = enum_to_string(severity);
        const std::string_view type_string = enum_to_string(type);

        const std::string output = std::format("[{}] {} {}: {} \n", current_time, severity_string, type_string, msg);
        logs += output;

        std::cout << output;
        std::cout.flush();
    }

    void Debug_logger::write_to_log_file() const
    {
        DEBUG_LOG(notification, engine, "Writing to log file");

        std::ofstream log_file("Log.txt");

        if (log_file.is_open())
        {
            log_file << logs;
            log_file.close();
        }
        else
            DEBUG_LOG(error, engine, "Failed to open log file");
    }

    bool Debug_logger::is_log_alloved(Log_severity severity, Log_type type)
    {
        if (m_disabled_severities.has_flag(severity))
            return false;

        if (m_disabled_types.has_flag(type))
            return false;

        return true;
    }
} // namespace MEngine
