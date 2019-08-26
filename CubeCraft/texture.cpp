#include "texture.h"
#include <glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>

cc::resource_manager<cc::texture> cc::texture_manager::m_tex;

cc::texture cc::texture_manager::load(std::string dir) {
	return texture(dir);
}

void cc::texture_manager::add(std::string dir, std::string name) {
	m_tex.add(name, load(dir));
}

cc::texture cc::texture_manager::access(std::string dir) {
	return *m_tex.access(dir);
}

cc::texture::texture(std::string dir) {
	load(dir);
}

void cc::texture::load(std::string dir) {
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, alpha;
	unsigned char* data = stbi_load(dir.c_str(), &width, &height, &alpha, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else throw std::runtime_error("Failed to load texture");
	stbi_image_free(data);
	m_index = texture;
}

void cc::texture::bind() const noexcept {
	glBindTexture(GL_TEXTURE_2D, m_index);
}