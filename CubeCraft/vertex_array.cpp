#include "vertex_array.h"
#include <../glfw3.h>

cc::vertex_array::vertex_array() :
	m_object(0), m_ebo_size(0)
{
	glGenVertexArrays(1, &m_object);
}

void cc::vertex_array::enable_index (
	vertex_buffer* buffer, 
	GLuint index, GLint size, 
	GLenum type, 
	bool normalized, 
	GLsizei stride)
	const noexcept
{
	bind();
	buffer->bind_as(GL_ARRAY_BUFFER);
	glVertexAttribPointer(index, size, type, normalized ? GL_TRUE : GL_FALSE, stride, NULL);
	glEnableVertexAttribArray(index);
	buffer->bind0(GL_ARRAY_BUFFER);
}

void cc::vertex_array::use_ebo(vertex_buffer* ebo, GLsizei size) noexcept
{
	bind();
	ebo->bind_as(GL_ELEMENT_ARRAY_BUFFER);
	m_ebo_size = size == 0 ? ebo->size() / 4 : size;
	bind0();
}

void cc::vertex_array::set_texture(texture tex) noexcept {
	m_texture = tex;
}

void cc::vertex_array::draw_with_ebo(GLenum mode) const noexcept
{
	m_texture.bind();
	bind();
	glDrawElements(mode, m_ebo_size, GL_UNSIGNED_INT, NULL);
	bind0();
}

void cc::vertex_array::bind() const noexcept
{
	glBindVertexArray(m_object);
}

void cc::vertex_array::bind0() noexcept
{
	glBindVertexArray(0);
}
