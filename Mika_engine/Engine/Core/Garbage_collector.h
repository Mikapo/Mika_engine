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
        struct Tracked_obj
        {
            std::unique_ptr<Object> m_object = nullptr;
            bool m_is_checked = false;
        };

        using Object_ptr_container = std::unordered_map<const Object*, Tracked_obj>;

        /**
         * @param Object to check
         * @return Is object alive and tracked by garbage collector
         */
        [[nodiscard]] bool is_object_valid(const Object* obj) const;

        /**
         * @param Object to be registered to the garbage collector
         */
        void register_object(std::unique_ptr<Object> obj);

        /**
         * @return All objects that are tracked by the garbage collector
         */
        [[nodiscard]] const Object_ptr_container& get_registered_objects() const noexcept;

        /**
         * Sets object that is root of object tree
         *
         * @param Object to bet set as root
         */
        void set_root_object(Object* obj);

        // Handles garbage collector when necessary
        void update();

        // Cleanups all the objects tracked by garbage collector
        void cleanup();

    private:
        // Runs garbage collection
        void garbage_collect();

        // Marks object and it's children as checked by garbage collector
        void check_object(Tracked_obj& obj);

        // Prepares unmarked object to destruction
        void destruct_unchecked_objects();

        // Frees objects that has marked to be freed
        void finalize_destruction_on_objects();

        Object_ptr_container m_registered_objects;
        Object* m_root = nullptr;
    };

} // namespace MEngine
