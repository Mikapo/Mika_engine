#pragma once

class Key_event_listener
{
public:
	virtual void on_key_event(int32_t key, int32_t scancode, int32_t action, int32_t mods) = 0;
};
