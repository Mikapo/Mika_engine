#pragma once

#include "Datatypes/Frame_data.h"
#include "Scene_component.h"

namespace Mika_engine
{
    class Light_component : public Scene_component
    {
        GENERATED_BODY(Light_component)

    public:
        void initialize() override;
        void set_color(glm::vec4 color) noexcept;
        Light_data get_light_data() const noexcept;

    private:
        glm::vec4 m_color = {1.0f, 1.0f, 1.0f, 1.0f};
    };

} // namespace Mika_engine
