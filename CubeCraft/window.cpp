#include "window.h"
#include <stdexcept>
#include <GL/glew.h>

cc::window::window(const std::string title, int width, int height, int x, int y)
	:m_window(SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL))
{
	if (!m_window) {
		throw std::runtime_error("Cannot create window.");
	}
	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context) {
		throw std::runtime_error("Cannot init GL.");
	}
	else {
		if (glewInit() != GLEW_OK) {
			throw std::runtime_error("Cannot init GL.");
		}
	}
}

cc::window::~window()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
}

void cc::window::swap_buffers() const noexcept
{
	SDL_GL_SwapWindow(m_window);
}

int cc::window::poll_event(cc::Event & event) const noexcept
{
	return SDL_PollEvent(&event);
}

void cc::window::make_current() const noexcept
{
	SDL_GL_MakeCurrent(m_window, m_context);
}
