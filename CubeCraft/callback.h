#pragma once
#define GLM_FORCE_RADIANS
#include <glfw3.h>

namespace cc {

	class callback_manager {
	public:
		static void process_input(GLFWwindow* window);
		static void on_reshape(GLFWwindow* window, int width, int height);
		static void cursor_pos(GLFWwindow* window, double x, double y);
		static void registry(GLFWwindow* window);
	};

}