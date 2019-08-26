#pragma once
#include <memory>
#include <functional>
#include <glad/glad.h>
#include "noncopyable.hpp"
#include <glm/glm.hpp>

namespace cc {
	class shader 
		/*:private noncopyable*/
	{
	public:
		shader(const char* vertexShaderSource, const char* fragmentShaderSource);
		void use() const noexcept;
		void uniform(const std::string& name, glm::mat4 val);
	private:
		std::unique_ptr<GLuint, std::function<void(GLuint *) noexcept>> m_program;
	};
};
