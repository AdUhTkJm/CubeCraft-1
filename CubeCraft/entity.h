#pragma once
#include <glm/glm.hpp>
#include "noncopyable.hpp"

namespace cc {

	//for deriving
	class entity : private noncopyable {
	public:
		entity(glm::vec3 pos, glm::vec3 rot = { 0, 0, 1 }) noexcept;
		glm::vec3 position() const noexcept;
		glm::vec3 front() const noexcept;
		void front(glm::vec3) noexcept;
	protected:
		glm::vec3 pos;
		glm::vec3 fr;
	};

	class player
		:public entity {
	public:
		player() noexcept;
		glm::vec3 move(glm::vec3 delta);
	};
	const float ent_speed = 0.5f;
	extern player ent_player;
}
