#pragma once

#include <cstdint>

class Renderer_item
{
public:
	virtual ~Renderer_item() = default;

	Renderer_item(const Renderer_item&) = delete;
	Renderer_item(Renderer_item&& other);
	
	void operator=(const Renderer_item&) = delete;
	void operator=(Renderer_item&& other);

	bool is_valid() const { return m_is_valid; }

protected:
	Renderer_item() {};

	uint32_t m_id = 0;

private:
	bool m_is_valid = true;
};

