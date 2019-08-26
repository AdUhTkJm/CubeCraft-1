#include "vertex_buffer.h"
#include <stdexcept>

cc::vertex_buffer::vertex_buffer(GLuint size, void * data, GLenum usage)
	:m_size(size)
{
	glGenBuffers(1, &m_buffer);
	bind_as(GL_ARRAY_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	bind0(GL_ARRAY_BUFFER);
}

cc::vertex_buffer::~vertex_buffer() noexcept
{
	glDeleteBuffers(1, &m_buffer);
}

void cc::vertex_buffer::data(GLuint size, void * data, GLuint offset) const
{
	bind_as(GL_ARRAY_BUFFER);
	if (size + offset > m_size) {
		throw std::runtime_error("Cannot change vertex buffer data: size not enough.");
	}
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	bind0(GL_ARRAY_BUFFER);
}

void cc::vertex_buffer::data(void * data) const
{
	bind_as(GL_ARRAY_BUFFER);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_size, data);
	bind0(GL_ARRAY_BUFFER);
}

void cc::vertex_buffer::bind_as(GLenum target) const noexcept
{
	glBindBuffer(target, m_buffer);
}

GLuint cc::vertex_buffer::size() const noexcept
{
	return m_size;
}

void cc::vertex_buffer::bind0(GLenum target) noexcept
{
	glBindBuffer(target, 0);
}
