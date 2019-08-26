#pragma once
#include <glad/glad.h>
#include <cstddef>
#include "noncopyable.hpp"

namespace cc {
	class vertex_buffer 
		:private noncopyable
	{
	public:
		vertex_buffer(GLuint size, void * data = NULL, GLenum usage = GL_STATIC_DRAW);
		~vertex_buffer() noexcept;
		void data(GLuint size, void * data, GLuint offset) const;
		void data(void * data) const;
		void bind_as(GLenum target) const noexcept;
		static void bind0(GLenum target = GL_ARRAY_BUFFER) noexcept;
		GLuint size() const noexcept;
	private:
		GLuint m_buffer;
		GLuint m_size;
	};
};
