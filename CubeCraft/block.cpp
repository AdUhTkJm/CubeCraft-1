#define GLM_FORCE_RADIANS

#include "block.h"
#include "shader_manager.h"
#include "vertex_array.h"
#include "entity.h"
#include <vector>
#include <crtdbg.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

cc::block::block(block_type ty) noexcept:
	m_id(ty) {
}

void cc::block::draw(glm::ivec3 delta) const {
	static GLfloat* vdata = new GLfloat[120]{
		//front
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		//back
		1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		//right
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		//left
		0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		//top
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		//bottom
		1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f
	};
	static GLuint* edata = new GLuint[36]{
		0, 1, 3,
		1, 2, 3,

		4, 5, 7,
		5, 6, 7,

		8, 9, 11,
		9, 10, 11,

		12, 13, 15,
		13, 14, 15,

		16, 17, 19,
		17, 18, 19,

		20, 21, 23,
		21, 22, 23
	};

	static cc::vertex_array vao;
	static cc::vertex_buffer* vbo = new cc::vertex_buffer(480);
	static cc::vertex_buffer* vbo_2 = new cc::vertex_buffer(480, vdata + 3);
	static cc::vertex_buffer* ebo = new cc::vertex_buffer(144, edata);
	if (m_id == air) return;
	for (int i = 0; i < 24; ++i)
		vdata[i * 5 + 0] += delta.x,
		vdata[i * 5 + 1] += delta.y, 
		vdata[i * 5 + 2] += delta.z;
	vbo->data(vdata);
	vao.enable_index(vbo, 0, sizeof(float), GL_FLOAT, false, sizeof(float) * 5);
	vao.enable_index(vbo_2, 1, sizeof(float), GL_FLOAT, false, sizeof(float) * 5);
	vao.use_ebo(ebo);
	vao.set_texture(texture_manager::access(std::to_string(m_id)));
	vao.draw_with_ebo(GL_TRIANGLES);

	for (int i = 0; i < 24; ++i)
		vdata[i * 5 + 0] -= delta.x,
		vdata[i * 5 + 1] -= delta.y,
		vdata[i * 5 + 2] -= delta.z;
}

void cc::block_registry::registry(block_type ty, std::string dir) {
	texture_manager::add(dir, std::to_string(ty));
}
