#pragma once
#include <string>
#include <glad/glad.h>
#include "noncopyable.hpp"
#include <../glfw3.h>

namespace cc {
	class window 
		:private noncopyable
	{
	public:
		explicit window(const std::string title = "", int width = 800, int height = 600,
			int x = 0, int y = 0);
		~window() noexcept;
		void swap_buffers() const noexcept;
		bool should_close() const noexcept;
		void poll_events() const;
		double aspect() const;
		GLFWwindow* self() { return m_window; }
	private:
		GLFWwindow* m_window;
	};
};
