#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

namespace MEngine
{
    class Object;
    class Garbage_collector
    {
    public:
        bool is_object_valid(const Object* obj) const;
        void register_object(std::unique_ptr<Object> obj);
        const std::unordered_map<Object*, std::unique_ptr<Object>>& get_registered_objects() const noexcept;
        void set_root_object(Object* obj);
        void update();
        void cleanup();

    private:
        void garbage_collect();
        void check_object(Object* obj);
        void destruct_unchecked_objects();
        void finalize_destruction_on_objects();

        std::unordered_map<Object*, std::unique_ptr<Object>> m_registered_objects;
        Object* m_root = nullptr;
    };

} // namespace MEngine
