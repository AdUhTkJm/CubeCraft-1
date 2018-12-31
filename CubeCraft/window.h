#pragma once
#include <string>
#include <SDL/SDL_video.h>
#include <SDL/SDL_events.h>
#include "noncopyable.hpp"

namespace cc {
	using Event = SDL_Event;
	class window 
		:private noncopyable
	{
	public:
		window(const std::string title = "", int width = 800, int height = 600,
			int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED);
		void swap_buffers() const noexcept;
		int poll_event(Event & event) const noexcept;

	private:
		SDL_Window * m_window;
		SDL_GLContext m_context;
	};
};
