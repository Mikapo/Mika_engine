#pragma once

#include <unordered_set>

struct GLFWwindow;
class Mika_engine;
class UI;
class UI_renderer
{
public:
	void initialize(GLFWwindow* window, Mika_engine* engine);
	void cleanup();
	void render_ui(std::unordered_set<UI*>& viewport);

private:
	Mika_engine* m_engine = nullptr;
	bool m_has_been_initialized = false;
};

