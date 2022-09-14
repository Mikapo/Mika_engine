#pragma once

#include "Utility/Macros/Helper_macros.h"
#include <array>
#include <format>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <string_view>
#include <unordered_map>

namespace Mika_engine
{
    DECLARE_ENUM(Log_severity, uint8_t, error, warning, notification)
    DECLARE_ENUM(Log_type, uint8_t, objects, render, opengl, application, engine, garbage_collector, other)

    class Debug_logger
    {
    public:
        static Debug_logger& get() noexcept;
        void log(Log_severity severity, Log_type type, std::string_view msg);
        void write_to_log_file() const;

    private:
        Debug_logger() = default;

        std::string get_time_string() const;
        bool is_log_alloved(Log_severity severity, Log_type type);

        bool m_writes_to_log_file = true;
        std::string logs;
        std::unordered_map<Log_severity, bool> m_enabled_severities;
        std::unordered_map<Log_type, bool> m_enabled_types;
    };

#ifdef _DEBUG
#define LOG(severity, type, msg, ...)                                                                                  \
    Debug_logger::get().log(Log_severity::severity, Log_type::type, std::format(msg, __VA_ARGS__))

#else
#define LOG(...)
#endif
}
