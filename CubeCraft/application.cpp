#include "application.h"
#include "window.h"
#include "vertex_array.h"
#include "shader_manager.h"
#include "block_manager.h"
#include "callback.h"
#include "entity.h"
#include <../glfw3.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

cc::application::application() :m_window("CubeCraft 0.1", 800, 800, 300, 100) { }

void cc::application::run() noexcept {
	cc::vertex_array vao;
	cc::shader& s = cc::shader_manager::add_shader("default", "default.vert", "default.frag");
	s.use();
	s.uniform("proj", glm::perspective(glm::radians(glm::radians(3000.0f)), (float)m_window.aspect(), 0.1f, 1000.0f));
	glClearColor(0.4f, 0.5f, 0.6f, 0.7f);
	glEnable(GL_DEPTH_TEST);
	while (!m_window.should_close()) {
		callback_manager::process_input(m_window.self());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		s.uniform("view", glm::lookAt(ent_player.position(), ent_player.position() + ent_player.front(), { 0, 1, 0 }));
		world::render();
		m_window.swap_buffers();
		m_window.poll_events();
	}
}
