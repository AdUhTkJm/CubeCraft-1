#pragma once
#include <glm/glm.hpp>
#include <string>
#include "blockdef.hpp"

namespace cc {

	class block {
	private:
		block_type m_id;
	public:
		block(block_type ty = air) noexcept;
		void draw(glm::ivec3 delta) const;
	};

	class block_registry {
	public:
		static void registry(block_type ty, std::string dir);
	};

}
