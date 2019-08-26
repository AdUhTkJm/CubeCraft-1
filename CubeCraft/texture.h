#pragma once
#include <string>
#include <glad/glad.h>
#include "resource_manager.hpp"

namespace cc {

	class texture {
	private:
		GLuint m_index;
	public:
		texture() {}
		texture(std::string dir);
		void load(std::string dir);
		void bind() const noexcept;
	};

	class texture_manager {
	private:
		static texture load(std::string dir);
		static resource_manager<texture> m_tex;
	public:
		static void add(std::string dir, std::string name);
		static cc::texture access(std::string dir);
	};

}