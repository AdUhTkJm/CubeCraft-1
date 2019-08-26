#pragma once
#include <memory>
#include "vertex_buffer.h"
#include "texture.h"

namespace cc {
	class vertex_array 
		:private noncopyable
	{
	public:
		vertex_array();
		void enable_index(
			vertex_buffer* buffer,
			GLuint index, GLint size = 4, 
			GLenum type = GL_FLOAT,
			bool normalized = false, GLsizei stride = 0) const noexcept;
		void use_ebo(vertex_buffer* ebo, GLsizei size = 0) noexcept;
		void set_texture(texture tex) noexcept;
		void draw_with_ebo(GLenum mode = GL_TRIANGLE_STRIP) const noexcept;
	private:
		void bind() const noexcept;
		static void bind0() noexcept;
		GLuint m_object;
		GLuint m_ebo_size;
		texture m_texture;
	};
}
