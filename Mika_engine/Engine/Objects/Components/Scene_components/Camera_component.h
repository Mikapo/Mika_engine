#pragma once

#include "Scene_component.h"

#include "Datatypes/Frame_data.h"

class Camera_component : public Scene_component
{
    GENERATED_BODY(Camera_component)

public:
	float get_min_clip() const;
	float get_max_clip() const;
	float get_fov() const;
	void set_min_clip(float min_clip);
	void set_max_clip(float max_clip);
	void set_fov(float fov);
	Camera_data get_camera_data() const;

private:
	float m_min_clip = 0.1f;
	float m_max_clip = 100.0f;
	float m_fov = 50.0f;
};

