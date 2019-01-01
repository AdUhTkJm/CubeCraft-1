#pragma once
#include <glm/glm.hpp>
#include "noncopyable.hpp"

namespace cc {
	/*ºÃ≥–”√*/
	class entity 
		:private noncopyable
	{
	public:
		entity(glm::vec3 pos, glm::vec3 rot) noexcept;
	protected:
		glm::vec3 pos, rot;
	};
}
