#pragma once
#include "window.h"
#include "noncopyable.hpp"

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
