#pragma once
#include "window.h"
#include "noncopyable.hpp"
#include <../glfw3.h>

namespace cc {
	class application 
		:private noncopyable
	{
	public:
		application();
		void run() noexcept;
	private:
		bool running = true;
		window m_window;
	};
};
