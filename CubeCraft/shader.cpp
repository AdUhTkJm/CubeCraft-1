#include "shader.h"
#include <exception>
#include <glm/gtc/type_ptr.hpp>

cc::shader::shader(const char * vertexShaderSource, const char * fragmentShaderSource)
	:m_program(new GLuint(glCreateProgram()), [](GLuint * ptr) noexcept {glDeleteProgram(*ptr); delete ptr; })
{
	std::unique_ptr<GLuint, std::function<void(GLuint *)>>
		vertexShader(new GLuint(glCreateShader(GL_VERTEX_SHADER))
			, [](GLuint * ptr) {
				glDeleteShader(*ptr);
				delete ptr;
			}),
		fragmentShader(new GLuint(glCreateShader(GL_FRAGMENT_SHADER))
			, [](GLuint* ptr) {
				glDeleteShader(*ptr);
				delete ptr;
			});

	glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(*vertexShader);

	int success = 0;
	char szLog[512];
	glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*vertexShader, 512, NULL, szLog);
		printf(szLog);
		throw std::exception(szLog);
	}

	glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(*fragmentShader);

	glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*fragmentShader, 512, NULL, szLog);
		throw std::exception(szLog);
	}

	glAttachShader(*m_program, *vertexShader);
	glAttachShader(*m_program, *fragmentShader);
	glLinkProgram(*m_program);

	glGetProgramiv(*m_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(*m_program, 512, NULL, szLog);
		throw std::exception(szLog);
	}
}

void cc::shader::use() const noexcept
{
	glUseProgram(*m_program);
}

void cc::shader::uniform(const std::string & name, glm::mat4 val)
{
	int loc = glGetUniformLocation(*m_program.get(), name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}
