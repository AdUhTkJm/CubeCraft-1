#pragma once
#include "resource_manager.hpp"
#include "shader.h"

namespace cc {
	class shader_manager {
	private:
		static resource_manager<shader> m_shader;
	public:
		static shader& add_shader(const std::string& name, 
			const std::string& vertexFileName, 
			const std::string& fragmentFileName);
		static std::shared_ptr<cc::shader> access(const std::string& name);
	};
};
