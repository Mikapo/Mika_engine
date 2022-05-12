#pragma once

#include "Application.h"
#include "Garbage_collector.h"
#include "UI_renderer.h"
#include <thread>
#include <chrono>
#include "Scene_renderer.h"

class Mesh_data;
class Light_data;
class Camera_data;
class Key_event_listener;
class Object;
class World;

class Mika_engine
{
public:
	Mika_engine();

	template<typename T>
	void set_world()
	{
		World* world = Object::construct_object<T>(this);
		Object* world_object = world;
		m_world = world;
		m_garbage_collector.set_root_object(world);
	}

	void start();
	void register_object(Object* obj);
	void unregister_object(Object* obj);
	size_t get_amount_of_registered_objects();
	bool is_object_valid(Object* obj) const;
	void mark_object_for_destruction(Object* obj);
	void subscribe_for_key_events(Key_event_listener* listener);
	void send_mesh_to_render(Mesh_data& mesh);
	void send_light_to_render(Light_data& light);
	void send_camera_to_render(Camera_data& camera);
	float get_deltatime() const;
	void get_window_dimensions(int32_t& width, int32_t& height) const;
	float get_screen_aspect_ratio() const;
	void set_render_settings(Render_settings settings);
	Render_settings get_render_settings() const;

private:
	struct Input
	{
		int32_t key;
		int32_t scancode;
		int32_t action;
		int32_t mods;
	};

	void render();
	void update();
	void cleanup();
	void on_window_resize(int32_t width, int32_t height);
	void on_window_open(GLFWwindow* window);
	void update_deltatime();
	void on_key_event(int32_t key, int32_t scancode, int32_t action, int32_t mods);
	void handle_inputs();
	void setup_callbacks();

	Application m_application;
	Garbage_collector m_garbage_collector;
	Scene_renderer m_scene_renderer;
	UI_renderer m_ui_renderer;
	World* m_world = nullptr;

	std::thread m_update_thread;
	bool m_update_thread_stop_flag = false;
	bool m_first_logic_frame = true;
	float m_deltatime = 0.0f;
	int32_t m_window_width = 0, m_window_height = 0;
	float m_aspect_ratio = 0.0f;
	std::chrono::steady_clock::time_point m_time_since_last_frame;
	std::unordered_set<Key_event_listener*> m_key_event_listeners;
	std::vector<Input> m_inputs;
	
};
