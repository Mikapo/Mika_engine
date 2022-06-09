#pragma once

#include <stdint.h>
#include <string_view>
#include <iostream>

class Debug_logger
{
public:
    static Debug_logger& get();
    void log_OpenGL(
        uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t lenght, const char* msg, const void* data);
    void log_object_destroyed(std::string_view name, size_t obj_amount);
    void log_object_created(std::string_view name, size_t obj_amount);

 private:
    template<typename... string_types>
    void print_engine_log(string_types... strings)
    {
        std::cout << "------------Engine debug------------\n";
        ((std::cout << strings << "\n"), ...);
        std::cout << "------------------------------------\n";
        std::cout.flush();
    }

    bool m_OpenGL_debug_messages_enabled = false;
    bool m_engine_debug_messages_enabled = false;
};