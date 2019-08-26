#include "window.h"
#include "callback.h"
#include "block_manager.h"
#include <stdexcept>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*namespace {
	void on_reshape(GLFWwindow* window,int width, int height) {
		cc::shader_manager::access("default").uniform("model", glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f));
	}
}*/

cc::window::window(const std::string title, int width, int height, int x, int y)
{
	if (!glfwInit())
		throw std::runtime_error("Unable to initialize the Graphics Library");
	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwMakeContextCurrent(m_window);
	glfwSetWindowPos(m_window, x, y);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	callback_manager::registry(m_window);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	block_registry::registry(grass, ".\\texture\\grassen.bmp");
	block_registry::registry(dirt, ".\\texture\\dirt.bmp");
	block_registry::registry(stone, ".\\texture\\stone.bmp");
	block_registry::registry(bedrock, ".\\texture\\bedrock.bmp");

	world::erect();
}

cc::window::~window() noexcept
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void cc::window::swap_buffers() const noexcept
{
	glfwSwapBuffers(m_window);
}

bool cc::window::should_close() const noexcept
{
	return glfwWindowShouldClose(m_window);
}

void cc::window::poll_events() const
{
	glfwPollEvents();
}

double cc::window::aspect() const {
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	return double(w) / h;
}
