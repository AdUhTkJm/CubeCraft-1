#include "shader_manager.h"
#include <sstream>
#include <fstream>
#include <stdexcept>

cc::resource_manager<cc::shader> cc::shader_manager::m_shader;

cc::shader& cc::shader_manager::add_shader(const std::string & name, const std::string & vertexFileName, const std::string & fragmentFileName) {
	std::ifstream verFile(vertexFileName), fragFile(fragmentFileName);
	if (!verFile || !fragFile) {
		throw std::runtime_error("Cannot open file(s) during compiling shader(s)");
	}
	std::stringstream verStream, fragStream;
	verStream << verFile.rdbuf();
	fragStream << fragFile.rdbuf();

	verFile.close();
	fragFile.close();

	std::string 
		strVerSource = verStream.str(),
		strFragSource = fragStream.str();

	static const char
		*szVerSource = strVerSource.c_str(),
		*szFragSource = strFragSource.c_str();

	return m_shader.add(name, szVerSource, szFragSource);
}

std::shared_ptr<cc::shader> cc::shader_manager::access(const std::string& name) {
	return m_shader.access(name);
}
