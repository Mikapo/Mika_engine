#include "Debug_logger.h"
#include <format>
#include <GL/glew.h>

Debug_logger& Debug_logger::get() noexcept
{
    static Debug_logger logger;
    return logger;
}

void Debug_logger::log_OpenGL(
    uint32_t source, uint32_t type, uint32_t id, uint32_t severity , int32_t lenght, const char* msg, const void* data)
{
    if (!m_OpenGL_debug_messages_enabled)
        return;

    std::string_view source_string;
    std::string_view type_string;
    std::string_view severity_string;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        source_string = "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        source_string = "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        source_string = "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        source_string = "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        source_string = "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        source_string = "Source: Other";
        break;
    default:
        source_string = "Source: Unknown";
    }
    std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        type_string = "Type: Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        type_string = "Type: Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        type_string = "Type: Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        type_string = "Type: Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        type_string = "Type: Performance";
        break;
    case GL_DEBUG_TYPE_MARKER:
        type_string = "Type: Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        type_string = "Type: Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        type_string = "Type: Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER:
        type_string = "Type: Other";
        break;
    default:
        type_string = "Type: Unknown";
        break;
    }

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        severity_string = "Severity: High";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        severity_string = "Severity: Medium";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        severity_string = "Severity: Low";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        severity_string = "Severity: Notification";
        break;
    default:
        severity_string = "Severity: Unknown";
        break;
    }
   
    std::cout << "------------OpenGL debug------------\n";
    std::cout << "message: " << msg << "\n";
    std::cout << "source: " << source_string << "\n";
    std::cout << "type: " << type_string << "\n";
    std::cout << "severity: " << severity_string << "\n";
    std::cout << "------------------------------------\n";
    std::cout.flush();
}

void Debug_logger::log_object_destroyed(std::string_view name, size_t obj_amount)
{
    if (m_engine_debug_messages_enabled)
        print_engine_log("Object destroyed", std::format("Name: {}\nObj_amount: {}", name, obj_amount));
}

void Debug_logger::log_object_created(std::string_view name, size_t obj_amount)
{
    if (m_engine_debug_messages_enabled)
        print_engine_log("Object created", std::format("Name: {}\nObj_amount: {}", name, obj_amount));
}
