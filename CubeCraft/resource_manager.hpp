#pragma once
#include <string>
#include <memory>
#include <map>

namespace cc {
	template<typename T>
	class resource_manager {
	public:
		template<typename ...Args>
		T& add(const std::string& name, Args... args);
		template<typename Arg>
		T& add(const std::string& name, Arg arg);
		std::shared_ptr<T> access(const std::string& name);
		void remove(const std::string& name);
	private:
		std::map<std::string, std::shared_ptr<T>> m_resource;
	};
};

template<typename T>
template <typename ...Args>
T& cc::resource_manager<T>::add(const std::string& name, Args... args) {
	m_resource.insert(std::make_pair<std::string, std::shared_ptr<T>>(std::string(name), std::make_shared<T>(args...)));
	return *m_resource.at(name);
}

template<typename T>
template <typename Arg>
T& cc::resource_manager<T>::add(const std::string& name, Arg arg) {
	m_resource.insert(std::make_pair<std::string, std::shared_ptr<T>>(std::string(name), std::make_shared<T>(arg)));
	return *m_resource.at(name);
}

template<typename T>
void cc::resource_manager<T>::remove(const std::string& name) {
	m_resource.erase(name);
}

template<typename T>
std::shared_ptr<T> cc::resource_manager<T>::access(const std::string& name) {
	return m_resource.at(name);
}