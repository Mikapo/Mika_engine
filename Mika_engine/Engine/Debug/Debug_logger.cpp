#include "Debug_logger.h"
#include "gsl/gsl"
#include <GL/glew.h>
#include <chrono>
#include <ctime>
#include <fstream>

std::string Debug_logger::get_time_string() const
{
    using namespace std::chrono;

    const auto current_time = system_clock::now();
    const time_t time = system_clock::to_time_t(current_time);

    constexpr size_t size = 26;
    char buffer[size];
    ctime_s(buffer, size, &time);

    const std::string time_string = buffer;

    std::string_view value = enum_to_string(test::a);

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

    const std::string_view severity_string = get_severity_string(severity);
    const std::string_view type_string = get_type_string(type);

    const std::string current_date = get_time_string();

    std::stringstream stream;
    stream << "[" << current_date << "] " << severity_string << " " << type_string << ": " << msg << "\n";

    logs << stream.str();

    std::cout << stream.str();
    std::cout.flush();
}

void Debug_logger::write_to_log_file() const
{
    LOG(notification, engine, "Writing to log file");

    std::ofstream log_file("Log.txt");

    if (log_file.is_open())
    {
        log_file << logs.str();
        log_file.close();
    }
    else
        LOG(error, engine, "Failed to open log file");
}

bool Debug_logger::is_log_alloved(Log_severity severity, Log_type type)
{
    const auto is_severity_enabled = m_enabled_severities.find(severity);
    const auto is_type_enabled = m_enabled_types.find(type);

    if (is_severity_enabled == m_enabled_severities.end())
        m_enabled_severities.emplace(severity, true);
    else if (!is_severity_enabled->second)
        return false;

    if (is_type_enabled == m_enabled_types.end())
        m_enabled_types.emplace(type, true);
    else if (!is_type_enabled->second)
        return false;

    return true;
}

std::string_view Debug_logger::get_severity_string(Log_severity severity) const noexcept
{
    switch (severity)
    {
    case Log_severity::error:
        return "error";
    case Log_severity::warning:
        return "warning";
    case Log_severity::notification:
        return "notification";
    default:
        return "unkown";
    }
}

std::string_view Debug_logger::get_type_string(Log_type type) const noexcept
{
    switch (type)
    {
    case Log_type::objects:
        return "objects";
    case Log_type::render:
        return "render";
    case Log_type::application:
        return "application";
    case Log_type::engine:
        return "engine";
    default:
        return "unkown";
    }
}
