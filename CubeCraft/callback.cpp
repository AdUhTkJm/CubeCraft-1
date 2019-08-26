#include "callback.h"
#include "shader_manager.h"
#include "entity.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

inline glm::highp_vec3 zeroify(glm::highp_vec3 x) {
	x.y = 0;
	return x;
}

void cc::callback_manager::process_input(GLFWwindow* window) {
	float speed = ent_speed;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_A))
		cc::ent_player.move(-glm::normalize(zeroify(glm::cross(cc::ent_player.front(), glm::vec3(0, 1, 0)))) * speed);
	if (glfwGetKey(window, GLFW_KEY_D))
		cc::ent_player.move(glm::normalize(zeroify(glm::cross(cc::ent_player.front(), glm::vec3(0, 1, 0)))) * speed);
	if (glfwGetKey(window, GLFW_KEY_S))
		cc::ent_player.move(-speed * glm::normalize(zeroify(cc::ent_player.front())));
	if (glfwGetKey(window, GLFW_KEY_W))
		cc::ent_player.move(speed * glm::normalize(zeroify(cc::ent_player.front())));
	if (glfwGetKey(window, GLFW_KEY_SPACE))
		cc::ent_player.move({ 0, speed, 0 });
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		cc::ent_player.move({ 0, -speed, 0 });
	//printf("%f %f %f\n", ent_player.position().x, ent_player.position().y, ent_player.position().z);
}

void cc::callback_manager::on_reshape(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	cc::shader_manager::access("default")->uniform("proj", glm::perspective(glm::radians(glm::radians(3000.0f)), (float)width / (float)height, 0.1f, 1000.0f));
}

void cc::callback_manager::cursor_pos(GLFWwindow* window, double x, double y) {
	static bool init = false;
	static double last_x, last_y, yaw = 0, pitch = 0;
	static const double rate = 0.7;
	if (!init)
		last_x = x,
		last_y = y,
		init = true;
	double senst = 0.01, deltax = (x - last_x) * senst, deltay = (last_y - y) * senst;
	last_x = x;
	last_y = y;

	yaw += deltax;
	pitch += deltay;
	pitch = std::min(pitch, 89.0);
	pitch = std::max(pitch, -89.0);

	glm::vec3 front;
	front.x = cos(rate * yaw) * cos(rate * pitch);
	front.y = sin(rate * pitch);
	front.z = sin(rate * yaw) * cos(rate * pitch);
	ent_player.front(glm::normalize(front));
}

void cc::callback_manager::registry(GLFWwindow* window) {
	glfwSetFramebufferSizeCallback(window, on_reshape);
	glfwSetCursorPosCallback(window, cursor_pos);
}