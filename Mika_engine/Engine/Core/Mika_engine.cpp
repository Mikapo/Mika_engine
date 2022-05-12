#include "Mika_engine.h"

#include "Objects/Object.h"
#include "Objects/World.h"
#include "Interfaces/Key_event_listener.h"
#include "Scene_renderer.h"
#include <mutex>
#include <iostream>

Mika_engine::Mika_engine() : m_application("Engine window", 1000, 1000)
{}

void Mika_engine::start()
{
	m_first_logic_frame = true;
	setup_callbacks();
	m_update_thread = std::thread([this] {update(); });
	m_application.start();
}

void Mika_engine::setup_callbacks()
{
	m_application.on_window_open(this, &Mika_engine::on_window_open);
	m_application.set_render_callback(this, &Mika_engine::render);
	m_application.set_cleanup_callback(this, &Mika_engine::cleanup);
	m_application.set_on_key_event_callback(this, &Mika_engine::on_key_event);
	m_application.set_window_resize_callback(this, &Mika_engine::on_window_resize);
}

void Mika_engine::on_window_open(GLFWwindow* window)
{
	m_application.get_window_dimensions(m_window_width, m_window_height);
	m_aspect_ratio = static_cast<float>(m_window_width) / static_cast<float>(m_window_height);
	m_scene_renderer.update_window_size(m_window_width, m_window_height);
	m_ui_renderer.initialize(window, this);
}

void Mika_engine::register_object(Object* obj)
{
	m_garbage_collector.register_object(obj);
}

void Mika_engine::unregister_object(Object* obj)
{
	m_garbage_collector.unregister_object(obj);
}

size_t Mika_engine::get_amount_of_registered_objects()
{
	return m_garbage_collector.get_registered_objects().size();
}

bool Mika_engine::is_object_valid(Object* obj) const
{
	return m_garbage_collector.is_object_valid(obj);
}

void Mika_engine::mark_object_for_destruction(Object* obj)
{
	m_garbage_collector.mark_object_for_destruction(obj);
}

void Mika_engine::subscribe_for_key_events(Key_event_listener* listener)
{
	Object* obj = dynamic_cast<Object*>(listener);

	if (is_object_valid(obj))
		m_key_event_listeners.insert(listener);
}

void Mika_engine::send_mesh_to_render(Mesh_data& mesh)
{
	m_scene_renderer.add_mesh_to_render(mesh);
}

void Mika_engine::send_light_to_render(Light_data& light)
{
	m_scene_renderer.add_light_to_render(light);
}

void Mika_engine::send_camera_to_render(Camera_data& camera)
{
	m_scene_renderer.add_camera_to_render(camera);
}

float Mika_engine::get_deltatime() const
{
	return m_deltatime;
}

void Mika_engine::get_window_dimensions(int32_t& width, int32_t& height) const
{
	width = m_window_width;
	height = m_window_height;
}

float Mika_engine::get_screen_aspect_ratio() const
{
	if (m_window_width < 1.0f || m_window_height < 1.0f)
		return 0.0f;
	else
		return m_aspect_ratio;
}

void Mika_engine::set_render_settings(Render_settings settings)
{
	m_scene_renderer.set_render_settings(settings);
}

Render_settings Mika_engine::get_render_settings() const
{
	return m_scene_renderer.get_render_settings();
}

void Mika_engine::render()
{
	m_scene_renderer.render_frame();
	
	if(is_object_valid(m_world))
		m_ui_renderer.render_ui(m_world->get_viewport());
}

void Mika_engine::update_deltatime()
{
	using namespace std::chrono;

	auto time = high_resolution_clock::now();
	auto time_passed = time - m_time_since_last_frame;
	m_time_since_last_frame = time;

	// converting to seconds
	if (!m_first_logic_frame)
		m_deltatime = static_cast<float>(time_passed.count()) * 0.000000001f;
	else
		m_deltatime = true;
}

void Mika_engine::on_window_resize(int32_t width, int32_t height)
{
	m_window_width = width;
	m_window_height = height;
	m_aspect_ratio = static_cast<float>(m_window_width) / static_cast<float>(m_window_height);
	m_scene_renderer.update_window_size(width, height);
}

static std::mutex input_mutex;
void Mika_engine::on_key_event(int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
	std::lock_guard<std::mutex> lock(input_mutex);
	m_inputs.emplace_back(key, scancode, action, mods);
}


void Mika_engine::handle_inputs()
{
	std::lock_guard<std::mutex> lock(input_mutex);

	std::vector<Key_event_listener*> remove;

	for (Input input : m_inputs)
	{
		for (auto* listener : m_key_event_listeners)
		{
			Object* obj = dynamic_cast<Object*>(listener);

			if (is_object_valid(obj))
				listener->on_key_event(input.key, input.scancode, input.action, input.mods);
			else
				remove.push_back(listener);
		}
	}

	for (auto* listener : remove)
		m_key_event_listeners.erase(listener);

	m_inputs.clear();
}

void Mika_engine::update()
{
	if (is_object_valid(m_world))
		m_world->initialize();

	while (!m_update_thread_stop_flag)
	{
		const int32_t frames_behind = 2;
		if (m_scene_renderer.how_many_frames_behind() > frames_behind)
			continue;

		m_garbage_collector.update();
		update_deltatime();
		handle_inputs();

		if (is_object_valid(m_world))
		{
			m_world->update(m_deltatime);
			m_world->send_data_to_render();
		}
		
		m_scene_renderer.end_frame();
		m_first_logic_frame = false;
	}
}

void Mika_engine::cleanup()
{
	m_update_thread_stop_flag = true;
	m_update_thread.join();
	m_garbage_collector.cleanup();
	m_scene_renderer.cleanup();
	m_ui_renderer.cleanup();
}

